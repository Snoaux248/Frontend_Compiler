#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LexicalAnalyzer.h"

//Global variable for the current Token
Token currentToken;

//Global Variable for keeping track of the currentline to print out if there is a Syntax Error
int currentLine = 1;

//Declaring the global parse functions
void parse_P();
void parse_S();
void parse_patchedS();
void parse_SPrime();
void parse_C();
void parse_E();
void parse_EPrime();
void parse_T();
void parse_TPrime();
void parse_F();
void parse_O();

//Function for if the Syntax Error is found
void syntaxError(){
    printf("\nSyntax Parser Output:\n");
    printf("Error encounter on line %d: The next lexeme was %s and the next token was %s\n",
           currentLine,
           currentToken.lexeme,
           getTokenString(currentToken.type));
    exit(1);
}


void correctType(int expectedType){
    if(currentToken.type == expectedType){
        printf("%s\t%s\n", currentToken.lexeme, getTokenString(currentToken.type));
        currentToken = getNextToken();
    }else{
        syntaxError();
    }
}

// Grammar Rule: P ::= S
void parse_P(){
    parse_S();
}

// Grammar Rule (After LeftWise Recursion was fixed)
// S ::= patchedS S'
// S' ::= ; S S' | ε
void parse_S(){
    parse_patchedS();
    parse_SPrime();
}
// Grammar Rule:
// patchedS ::= V := E
//           | O
//           | read(V)
//           | print(E)
//           | if C: begin S end
//           | if C: begin S else: S end
void parse_patchedS() {
    if (currentToken.type == IDENT) {
        correctType(IDENT);
        correctType(ASSIGN_OP);
        parse_E();
    }
    else if (currentToken.type == INC_OP || currentToken.type == DEC_OP) {
        parse_O();
    }
    else if (currentToken.type == KEY_READ) {
        correctType(KEY_READ);
        correctType(LEFT_PAREN);
        correctType(IDENT);
        correctType(RIGHT_PAREN);
    }
    else if (currentToken.type == KEY_PRINT) {
        correctType(KEY_PRINT);
        correctType(LEFT_PAREN);
        parse_E();
        correctType(RIGHT_PAREN);
    }
    else if (currentToken.type == KEY_IF) {
        correctType(KEY_IF);
        parse_C();
        correctType(COLON);
        correctType(KEY_BEGIN);
        parse_S();


        if (currentToken.type == KEY_ELSE) {
            correctType(KEY_ELSE);
            correctType(COLON);
            parse_S();
            correctType(KEY_END);
    // end after ELSE
        } else {
            correctType(KEY_END);  // end with no ELSE
        }
    }
    else {
        syntaxError();
    }
}


void parse_SPrime(){
    if(currentToken.type == SEMICOLON){
        correctType(SEMICOLON);
        parse_S();
        parse_SPrime();
    }
}

// Grammar Rule
// C ::= E < E | E > E | E = E | E <> E | E <= E | E >= E
void parse_C(){
    parse_E();
    if(currentToken.type == LESSER_OP ||
       currentToken.type == GREATER_OP ||
       currentToken.type == EQUAL_OP ||
       currentToken.type == NEQUAL_OP ||
       currentToken.type == LEQUAL_OP ||
       currentToken.type == GEQUAL_OP){

        correctType(currentToken.type);
       }else{
            syntaxError();
       }

    parse_E();
}

// Grammar Rule (After LeftWise Recursion was fixed)
// E ::= T E'
// E' ::= + T E' | - T E' | ε
void parse_E(){
    parse_T();
    parse_EPrime();
}
void parse_EPrime(){
    if(currentToken.type == ADD_OP){
        correctType(ADD_OP);
        parse_T();
        parse_EPrime();
    }
    else if(currentToken.type == SUB_OP){
        correctType(SUB_OP);
        parse_T();
        parse_EPrime();
    }
}

// Grammar Rule (After LeftWise Recursion was fixed)
// T ::= F T'
// T' ::= * F T' | / F T' | ** F T' | ε
void parse_T(){
    parse_F();
    parse_TPrime();
}
void parse_TPrime(){
    if(currentToken.type == MULT_OP){
        correctType(MULT_OP);
        parse_F();
        parse_TPrime();
    }
    else if(currentToken.type == DIV_OP){
        correctType(DIV_OP);
        parse_F();
        parse_TPrime();
    }
    else if(currentToken.type == POW_OP){
        correctType(POW_OP);
        parse_F();
        parse_TPrime();
    }
}

// Grammar Rule: F ::= (E) | N | V
void parse_F(){
    if(currentToken.type == LEFT_PAREN){
        correctType(LEFT_PAREN);
        parse_E();
        correctType(RIGHT_PAREN);
    }
    else if(currentToken.type == INT_LIT){
        correctType(INT_LIT);
    }
    else if(currentToken.type == IDENT){
        correctType(IDENT);
    }
    else{
        syntaxError();
    }
}

// Grammar Rule: O ::= ++V | --V
void parse_O(){
    if(currentToken.type == INC_OP){
        correctType(INC_OP);
        correctType(IDENT);
    }
    else if(currentToken.type == DEC_OP){
        correctType(DEC_OP);
        correctType(IDENT);
    }
    else{
        syntaxError();
    }
}

//Main Function to run the Lexical Analyzer and Syntax Parser
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: No input file provided.\n");
        return 2;
    }

    FILE *testFile = fopen(argv[1], "r");
    if (testFile == NULL) {
        printf("Error: Cannot open file %s\n", argv[1]);
        return 3;
    }
    fclose(testFile);

    printf("Lexical Analysis Output:\n");

    // Open file and initialize first token
    fileopen(argv[1]);
    currentToken = getNextToken();

    // Start parsing from the root
    parse_P();


    // Check for unexpected tokens after parse
    if (currentToken.type == UNKNOWN) {
        printf("\nSyntax Parser Output:\n");
        printf("Valid Syntax\n");
    } else {
        syntaxError();
    }

    return 0;
}
