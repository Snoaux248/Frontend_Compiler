# Frontend Compiler

**Author**: Ethan Childs  
**Language**: C  
**Project Type**: Lexical Analyzer and Syntax Parser

**Backus-Naur Form (BNF) Rules**
In this frontend compiler I wrote Lexical and Syntax Analyzers capable of parsing source code 
files provided by the user written in a programming language called “Cooke”. The syntax for this language
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

**Grammar Rule (After Left Wise Recursion was fixed)** <br>
S ::= patchedS S' <br>
S' ::= ; S S' | ε <br>
E ::= T E' <br>
E' ::= + T E' | - T E' | ε <br>
T ::= F T' <br>
T' ::= * F T' | / F T' | ** F T' | ε <br>


**Lexemes and Tokens**
Lexeme formation is guided using the BNF rules in the grammar above. My compiler matched each lexeme
with its associated token. Invalid lexemes are assigned to a token group called UNKNOWN. The following
token names are used to identify each valid lexeme:

Lexemes_and_Tokens= { <br>
  ":=" -> "ASSIGN_OP",<br>
  "<"  -> "LESSER_OP",<br>
  ">"  -> "GREATER_OP",<br>
  "="  -> "EQUAL_OP",<br>
  "<>" -> "NEQUAL_OP",<br>
  "<=" -> "LEQUAL_OP",<br>
  ">=" -> "GEQUAL_OP",<br>
  "("  -> "LEFT_PAREN",<br>
  ")"  -> "RIGHT_PAREN",<br>
  "+"  -> "ADD_OP",<br>
  "-"  -> "SUB_OP",<br>
  "*"  -> "MULT_OP",<br>
  "/"  -> "DIV_OP",<br>
  "**" -> "POW_OP",<br>
  "++" -> "INC_OP",<br>
  "--" -> "DEC_OP",<br>
  ";"  -> "SEMICOLON",<br>
  ":"  -> "COLON",<br>
  "read"   -> "KEY_READ",<br>
  "print"  -> "KEY_PRINT",<br>
  "if"     -> "KEY_IF",<br>
  "else"   -> "KEY_ELSE",<br>
  "begin"  -> "KEY_BEGIN",<br>
  "end"    -> "KEY_END",<br>
  "V"      -> "IDENT",<br>
  "N"      -> "INT_LIT"<br>
};<br>

Note: The left hand side are the valid lexemes and the right side are the valid tokens for that lexeme in the Cooke Programming Language.

Note: on Semicolon Syntax, if you're making your own source files to compile, keep in mind how semicolons work in this language. The rule
S ::= S ; S means semicolons are used to separate statements—not to end them.
So, not every statement should end with a semicolon like in C or Java.
