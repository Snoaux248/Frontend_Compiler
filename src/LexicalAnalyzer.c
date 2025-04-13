#include <stdio.h>
#include <ctype.h>
#include "LexicalAnalyzer.h"

//Including my currentLine from SyntaxParser.c
extern int currentLine;
static FILE *sourceFile;
static char currentChar;
static int endOfFile = 0;

//Declaring fileopen from LexicalAnalyzer.h
void fileopen(const char *filename){
    sourceFile = fopen(filename, "r");
    if(sourceFile == NULL){
        printf("Error cannot open %s\n", filename);
        endOfFile = 1;
        return;
    }
//Setting currentChar to the first character in the file
    currentChar = fgetc(sourceFile);
    endOfFile = 0;
}

//Declaring getNextToken from LexicalAnalyzer.h that is using my Token structure from Token.h
Token getNextToken(){
    Token token;
    token.lexeme[0] = '\0';
//Using isspace from ctype.h to ignore whitespace
    while(isspace(currentChar)){
        if(currentChar == '\n'){
            currentLine++;
        }
        currentChar = fgetc(sourceFile);
    }
//Setting the end of the file to EOF and type UNKNOWN that was defined in my Token.h
    if(endOfFile || currentChar == EOF){
        endOfFile = 1;
        token.lexeme[0] = 'E';
        token.lexeme[1] = 'O';
        token.lexeme[2] = 'F';
        token.lexeme[3] = '\0';
        token.type = UNKNOWN;
        printf("Analysis has reached the End of your File\n");
        return token;
    }
//Dealing with the IDENTIFERS and KEYWORDS with isalpha to insure it starts with a character bounding it within the size 100 lexeme array from token.h
    if(isalpha(currentChar)){
        int i = 0;
        while(isalnum(currentChar) && i < MAX_LEXEME_LEN - 1){
            token.lexeme[i++] = currentChar;
            currentChar = fgetc(sourceFile);
        }
        token.lexeme[i] = '\0';
//Checking each if/else statement for each keyword
        if(token.lexeme[0] == 'r' && token.lexeme[1] == 'e' && token.lexeme[2] == 'a' && token.lexeme[3] == 'd' && token.lexeme[4] == '\0'){
            token.type = KEY_READ;
        }
        else if(token.lexeme[0] == 'p' && token.lexeme[1] == 'r' && token.lexeme[2] == 'i' && token.lexeme[3] == 'n' && token.lexeme[4] == 't' && token.lexeme[5] == '\0'){
           token.type = KEY_PRINT;
        }
        else if(token.lexeme[0] == 'i' && token.lexeme[1] == 'f' && token.lexeme[2] == '\0'){
            token.type = KEY_IF;
        }
        else if(token.lexeme[0] == 'e' && token.lexeme[1] == 'l' && token.lexeme[2] == 's' && token.lexeme[3] == 'e' && token.lexeme[4] == '\0'){
            token.type = KEY_ELSE;
        }
        else if(token.lexeme[0] == 'b' && token.lexeme[1] == 'e' && token.lexeme[2] == 'g' && token.lexeme[3] == 'i' && token.lexeme[4] == 'n' && token.lexeme[5] == '\0'){
            token.type = KEY_BEGIN;
        }
        else if(token.lexeme[0] == 'e' && token.lexeme[1] == 'n' && token.lexeme[2] == 'd' && token.lexeme[3] == '\0'){
            token.type = KEY_END;
        }
        else{
            token.type = IDENT;
        }
        return token;
    }

//Dealing with the Integer Literals with loop contained in the size 100 lexeme array from token.h
    if(isdigit(currentChar)){
        int i = 0;
        while(isdigit(currentChar) && i < MAX_LEXEME_LEN - 1){
            token.lexeme[i++] = currentChar;
            currentChar = fgetc(sourceFile);
        }
        token.lexeme[i] = '\0';
        token.type = INT_LIT;
        return token;
    }
//Dealing with Operators with if/else for each symbol
//Here I am combining the ASSIGN_OP with COLON because I could not find a way to make it valid without the else setting token.type to COLON;
    if(currentChar == ':'){
        token.lexeme[0] = currentChar;
        currentChar = fgetc(sourceFile);
        if(currentChar == '='){
            token.lexeme[1] = currentChar;
            token.lexeme[2] = '\0';
            token.type = ASSIGN_OP;
            currentChar = fgetc(sourceFile);
        }
        else{
            token.lexeme[1] = '\0';
            token.type = COLON;
        }
        return token;
    }

    if(currentChar == '<'){
        token.lexeme[0] = currentChar;
        currentChar = fgetc(sourceFile);
        if(currentChar == '='){
            token.lexeme[1] = currentChar;
            token.lexeme[2] = '\0';
            token.type = LEQUAL_OP;
            currentChar = fgetc(sourceFile);
        }
        else if(currentChar == '>'){
            token.lexeme[1] = currentChar;
            token.lexeme[2] = '\0';
            token.type = NEQUAL_OP;
            currentChar = fgetc(sourceFile);
        }
        else{
            token.lexeme[1] = '\0';
            token.type = LESSER_OP;
        }
        return token;
    }

    if(currentChar == '>'){
        token.lexeme[0] = currentChar;
        currentChar = fgetc(sourceFile);
        if(currentChar == '='){
            token.lexeme[1] = currentChar;
            token.lexeme[2] = '\0';
            token.type = GEQUAL_OP;
            currentChar = fgetc(sourceFile);
        }
        else{
            token.lexeme[1] = '\0';
            token.type = GREATER_OP;
        }
        return token;
    }

    if(currentChar == '='){
        token.lexeme[0] = currentChar;
        token.lexeme[1] = '\0';
        token.type = EQUAL_OP;
        currentChar = fgetc(sourceFile);
        return token;
    }

    if(currentChar == '+'){
        token.lexeme[0] = currentChar;
        currentChar = fgetc(sourceFile);
        if(currentChar == '+'){
            token.lexeme[1] = currentChar;
            token.lexeme[2] = '\0';
            token.type = INC_OP;
            currentChar = fgetc(sourceFile);
        }
        else{
            token.lexeme[1] = '\0';
            token.type = ADD_OP;
        }
        return token;

    }

    if(currentChar == '-'){
        token.lexeme[0] = currentChar;
        currentChar = fgetc(sourceFile);
        if(currentChar == '-'){
            token.lexeme[1] = currentChar;
            token.lexeme[2] = '\0';
            token.type = DEC_OP;
            currentChar = fgetc(sourceFile);
        }
        else{
            token.lexeme[1] = '\0';
            token.type = SUB_OP;
        }
        return token;
    }

    if(currentChar == '*'){
        token.lexeme[0] = currentChar;
        currentChar = fgetc(sourceFile);
        if(currentChar == '*'){
            token.lexeme[1] = currentChar;
            token.lexeme[2] = '\0';
            token.type = POW_OP;
            currentChar = fgetc(sourceFile);
        }
        else{
            token.lexeme[1] = '\0';
            token.type = MULT_OP;
        }
        return token;
    }

    if(currentChar == '/'){
        token.lexeme[0] = currentChar;
        token.lexeme[1] = '\0';
        token.type = DIV_OP;
        currentChar = fgetc(sourceFile);
        return token;
    }
//Dealing with the special character tokens with if/else in my token.h
    if(currentChar == '('){
        token.lexeme[0] = currentChar;
        token.lexeme[1] = '\0';
        token.type = LEFT_PAREN;
        currentChar = fgetc(sourceFile);
        return token;
       }

    if(currentChar == ')'){
        token.lexeme[0] = currentChar;
        token.lexeme[1] = '\0';
        token.type = RIGHT_PAREN;
        currentChar = fgetc(sourceFile);
        return token;
    }

    if(currentChar == ';'){
        token.lexeme[0] = currentChar;
        token.lexeme[1] = '\0';
        token.type = SEMICOLON;
        currentChar = fgetc(sourceFile);
        return token;
    }
//Returning the UNKNOWN token as a fallback
    token.lexeme[0] = currentChar;
    token.lexeme[1] = '\0';
    token.type = UNKNOWN;
    currentChar = fgetc(sourceFile);
    return token;

}

//function to convert the integers back into the strings defined in my token.h
char keyStrings[] = {"KEY_READ\0KEY_PRINT\0KEY_IF\0KEY_ELSE\0KEY_BEGIN\0KEY_END\0IDENT\0INT_LIT\0ASSIGN_OP\0LESSER_OP\0GREATER_OP\0EQUAL_OP\0NEQUAL_OP\0LEQUAL_OP\0GEQUAL_OP\0ADD_OP\0SUB_OP\0MULT_OP\0DIV_OP\0POW_OP\0INC_OP\0DEC_OP\0LEFT_PAREN\0RIGHT_PAREN\0SEMICOLON\0COLON\0UNKNOWN\0"};
int keyStarts[] = {0, 9, 19, 26, 35, 45, 53, 59, 67, 77, 87, 98, 107, 117, 127, 137, 144, 151, 159, 166, 173, 180, 187, 198, 210, 220, 226, 234};
const char* getTokenString(int tokenConvert){
    return &keyStrings[keyStarts[tokenConvert]];
} 


//Main function if you just want to only run the Lexical Analyzer
/*
int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Error you need to provide and input file");
        return 1;
    }

    fileopen(argv[1]);

    printf("Cooke Analyzer :: R11761566\n");

    Token token;
    while(!endOfFile){
        token = getNextToken();
        if(!endOfFile){
            printf("%s %s\n", token.lexeme, getTokenString(token.type));
        }
    }

    return 0;

}*/








