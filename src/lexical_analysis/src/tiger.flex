%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <tokens.h>
#include <scanner_utils.h>

#define RETURN_TOK(TOK)         char_pos += yyleng; return TOK; 

#define LEAVE_STATE(TOK)        current_state = comment_caller; \
                                BEGIN(comment_caller); return TOK;

#define ENTER_STATE(STATE, TOK)         do { \
                                            comment_caller = current_state; \
                                            current_state = STATE; \
                                            BEGIN(STATE); \
                                            return TOK; \
                                        } while(0)

#define RETURN_RESERVED(TOK)    do { \
                                    yyless(yyleng - 1);  \
                                    RETURN_TOK(TOK); \
                                } while(0)

extern YYSTYPE yylval;

int char_pos = 1;
int line_num = 1;
int comment_caller = 0;
int current_state = 0;

/**
* \brief Used by (F)LEX to decide whether the tokenization is finished
upon reaching the end of the current input stream.
*
* When the scanner receives an end-of-file indication from YY_INPUT it calls
* yywrap(). If the latter returns zero, than the scanning continues
* (a file pointed at from yyin will be processed). If any other value is
* returned, the tokenizing is considered to be finished, and the scanner
* terminates and return 0 to the caller.  
*/
int yywrap(void) {
    char_pos = 1;
    return 1;
}

%}

/*  exclusive condition that is activated when a comment openning token 
 *  is encountered 
 */
%x S_COMMENT
%x S_STRING
%s S_BRACKET
%s S_PAREN
%s S_BRACE

DELIM       [ \t\n]+
VAR_SYMB    [a-zA-Z_]


%%

<S_COMMENT>"*/"         { LEAVE_STATE(IGNORE); }
<S_COMMENT>[^"*/"]*     { RETURN_TOK(IGNORE); }
<S_STRING>"\""          { LEAVE_STATE(IGNORE); }
<S_STRING>[^"]*         { yylval.sval = yytext; return STR_VAL; }
<S_BRACE>"}"            { LEAVE_STATE(RBRACE); }
<S_BRACKET>"]"          { LEAVE_STATE(RBRACK); }
<S_PAREN>")"            { LEAVE_STATE(RPAREN); }
[0-9]*                  { yylval.ival = atoi(yytext); return NUM_VAL; }
":="                    { RETURN_TOK(ASSIGN); }
":"                     { RETURN_TOK(COLON); }
"{"                     { ENTER_STATE(S_BRACE, LBRACE); }
"["                     { ENTER_STATE(S_BRACKET, LBRACK); }
"("                     { ENTER_STATE(S_PAREN, LPAREN); }
"/*"                    { ENTER_STATE(S_COMMENT, IGNORE); }
"\""                    { ENTER_STATE(S_STRING, IGNORE); }
string[^{VAR_SYMB}]     { RETURN_RESERVED(STRING); }
let[^{VAR_SYMB}]           { RETURN_RESERVED(LET); }
var[^{VAR_SYMB}]           { RETURN_RESERVED(VAR); }
type[^{VAR_SYMB}]          { RETURN_RESERVED(TYPE); }        
of[^{VAR_SYMB}]            { RETURN_RESERVED(OF); }        
array[^{VAR_SYMB}]         { RETURN_RESERVED(ARRAY); }        
in[^{VAR_SYMB}]            { RETURN_RESERVED(IN); }        
int[^{VAR_SYMB}]           { RETURN_RESERVED(INT); }        
end[^{VAR_SYMB}]           { RETURN_RESERVED(END); }        
while[^{VAR_SYMB}]         { RETURN_RESERVED(WHILE); }        
do[^{VAR_SYMB}]            { RETURN_RESERVED(DO); }        
function[^{VAR_SYMB}]      { RETURN_RESERVED(FUNCTION); }        
"+"                     { RETURN_TOK(PLUS); }
"-"                     { RETURN_TOK(MINUS); }
"*"                     { RETURN_TOK(TIMES); }
"/"                     { RETURN_TOK(DIVIDE); } 
";"                     { RETURN_TOK(SEMICOLON); }
"="                     { RETURN_TOK(EQ); }
"<"                     { RETURN_TOK(LT); }
"<="                    { RETURN_TOK(LE); } 
">"                     { RETURN_TOK(GT); }
">="                    { RETURN_TOK(GE); }
"&"                     { RETURN_TOK(AND); }
"|"                     { RETURN_TOK(OR); }
","                     { RETURN_TOK(COMMA); }
"."                     { RETURN_TOK(DOT); }
[a-zA-Z_][a-zA-Z_0-9]*    { yylval.sval = yytext; return ID; }
[ \t]+                  { RETURN_TOK(IGNORE); }
<*>\n                   { line_num++; char_pos = 1; return IGNORE; }
.                       { char_pos += yyleng; return -1;}
