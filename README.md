# Frontend Compiler

**Author**: Ethan Childs  
**Language**: C  
**Project Type**: Lexical and Syntax Analyzer

**Backus-Naur Form (BNF) Rules**
In this frontend compiler I wrote Lexical and Syntax Analyzers capable of parsing source code 
files provided by the user written in a new programming language called “Cooke”. The syntax for this language
will be based upon the following grammar (in BNF):

P ::= S  
S ::= V := E  
     | O  
     | read(V)  
     | print(E)  
     | if C: begin S end  
     | if C: begin S else: S end  
     | S ; S  
C ::= E < E  
     | E > E  
     | E = E  
     | E <> E  
     | E <= E  
     | E >= E  
E ::= T + E  
     | T - E  
     | T  
T ::= F * T  
     | F / T  
     | F ** F  
     | F  
F ::= (E)  
     | N  
     | V  
O ::= ++V  
     | --V  
V ::= a | b | ... | z | aV | bV | ... | yV | zV  
N ::= 0 | 1 | ... | 9 | 0N | 1N | ... | 8N | 9N

Note: The V and N grammar rules define the structure for identifiers (V) and integer literals (N), respectively.

Note: in my parser I accounted for the left wise recursion problem with the following adjustments 

**Grammar Rule (After Left Wise Recursion was fixed)**
S ::= patchedS S'
S' ::= ; S S' | ε
E ::= T E'
E' ::= + T E' | - T E' | ε
T ::= F T'
T' ::= * F T' | / F T' | ** F T' | ε


**Lexemes and Tokens**
Lexeme formation is guided using the BNF rules in the grammar above. My compiler matched each lexeme
with its associated token. Invalid lexemes are assigned to a token group called UNKNOWN. The following
token names are used to identify each valid lexeme:

Lexemes_and_Tokens= {
  ":=" -> "ASSIGN_OP",
  "<"  -> "LESSER_OP",
  ">"  -> "GREATER_OP",
  "="  -> "EQUAL_OP",
  "<>" -> "NEQUAL_OP",
  "<=" -> "LEQUAL_OP",
  ">=" -> "GEQUAL_OP",
  "("  -> "LEFT_PAREN",
  ")"  -> "RIGHT_PAREN",
  "+"  -> "ADD_OP",
  "-"  -> "SUB_OP",
  "*"  -> "MULT_OP",
  "/"  -> "DIV_OP",
  "**" -> "POW_OP",
  "++" -> "INC_OP",
  "--" -> "DEC_OP",
  ";"  -> "SEMICOLON",
  ":"  -> "COLON",
  "read"   -> "KEY_READ",
  "print"  -> "KEY_PRINT",
  "if"     -> "KEY_IF",
  "else"   -> "KEY_ELSE",
  "begin"  -> "KEY_BEGIN",
  "end"    -> "KEY_END",
  "V"      -> "IDENT",
  "N"      -> "INT_LIT"
};

Note: The left hand side are the valid lexemes and the right side are the valid tokens for that lexeme in the Cooke Programming Language.

Note on Semicolon Syntax

If you're making your own source files to compile, keep in mind how semicolons work in this language. The rule
S ::= S ; S means semicolons are used to separate statements—not to end them.
So, not every statement should end with a semicolon like in C or Java.
