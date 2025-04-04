#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

//Tokens for Identifiers and Integer Literals
#define IDENT 1
#define INT_LIT 2

//Tokens for Operators
#define ASSIGN_OP 3
#define LESSER_OP 4
#define GREATER_OP 5
#define EQUAL_OP 6
#define NEQUAL_OP 7
#define LEQUAL_OP 8
#define GEQUAL_OP 9
#define ADD_OP 10
#define SUB_OP 11
#define MULT_OP 12
#define DIV_OP 13
#define POW_OP 14
#define INC_OP 15
#define DEC_OP 16

//Tokens for Symbols
#define LEFT_PAREN 17
#define RIGHT_PAREN 18
#define SEMICOLON 19
#define COLON 20

//Tokens for Keywords
#define KEY_READ 21
#define KEY_PRINT 22
#define KEY_IF 23
#define KEY_ELSE 24
#define KEY_BEGIN 25
#define KEY_END 26

//Token for Unknowns
#define UNKNOWN 99

//Defining the size that this compiler can read per token
#define MAX_LEXEME_LEN 256



//Structure for the Tokens to be set as Integers and called into the LexicalAnalyzer.c
typedef struct{
    int type;
    char lexeme[MAX_LEXEME_LEN];

}Token;



#endif // TOKEN_H_INCLUDED
