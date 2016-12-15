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


%%

<S_STRING>"\""          { LEAVE_STATE(STRING); }
<S_STRING>[^"]*         { yylval.sval = yytext; return STR_VAL; }
<S_BRACE>"}"            { LEAVE_STATE(RBRACE); }
<S_BRACKET>"]"          { LEAVE_STATE(RBRACK); }
<S_BRACE>")"            { LEAVE_STATE(RPAREN); }
[0-9]*                  { yylval.ival = atoi(yytext); return NUM_VAL; }
<S_COMMENT>"*/"         { LEAVE_STATE(IGNORE); }
"\""                    { ENTER_STATE(S_STRING, STRING); }
":="                    { RETURN_TOK(ASSIGN); }
":"                     { RETURN_TOK(COLON); }
"{"                     { ENTER_STATE(S_BRACE, LBRACE); }
"["                     { ENTER_STATE(S_BRACKET, LBRACK); }
"("                     { ENTER_STATE(S_PAREN, LPAREN); }
"/*"                    { ENTER_STATE(S_COMMENT, IGNORE); }
"let"                   { RETURN_TOK(LET); }
"var"                   { RETURN_TOK(VAR); }
"type"                  { RETURN_TOK(TYPE); }
"of"                    { RETURN_TOK(OF); }
"array"                 { RETURN_TOK(ARRAY); }
"in"                    { RETURN_TOK(IN); }
"int"                   { RETURN_TOK(INT); }
"end"                   { RETURN_TOK(END); }
"+"                     { RETURN_TOK(PLUS); }
"-"                     { RETURN_TOK(MINUS); }
"*"                     { RETURN_TOK(TIMES); }
"/"                     { RETURN_TOK(DIVIDE); } 
";"                     { RETURN_TOK(SEMICOLON); }
"="                     { RETURN_TOK(EQ); }
[a-zA-Z][a-zA-Z0-9]*    { yylval.sval = yytext; return ID; }
[ \t]+                  { RETURN_TOK(SPACE); }
<*>\n                   { line_num++; char_pos = 1; return IGNORE; }
.                       { char_pos += yyleng; return -1;}
<S_COMMENT>[^(*/)]*   { return IGNORE; }
