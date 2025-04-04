#ifndef LEXICALANALYZER_H_INCLUDED
#define LEXICALANALYZER_H_INCLUDED

#include "token.h"

//Function to open the source file and read the first character
void fileopen(const char *filename);

//Function to move from the first character that fileopen grabs
Token getNextToken();

//Function to end the program
void endAnalysis();

//Function to return the next token in SyntaxParser.c
const char* getTokenString(int tokenConvert);

#endif // LEXICALANALYZER_H_INCLUDED
