%{
#include <stdio.h>
#include <tokens.h>
#include <string.h>

int char_pos = 1;
int line_num = 1;
int comment_caller = 0;

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
%x S_COLON

%%

"\""            { comment_caller = INITIAL; BEGIN(S_STRING); return STRING; }
":"             { comment_caller = INITIAL; BEGIN(S_COLON); return IGNORE; }
<S_COLON>" "    { BEGIN(comment_caller); return COLON; }
<S_COLON>"="    { BEGIN(comment_caller); return ASSIGN; } 
<S_STRING>"\""  { BEGIN(comment_caller); return IGNORE; }
"/*"            { comment_caller = INITIAL; BEGIN(S_COMMENT); return IGNORE; }
"let"           { char_pos += yyleng; return LET; }
"var"           { char_pos += yyleng; return VAR; }
"type"          { char_pos += yyleng; return TYPE; }
[a-zA-Z0-9]*    { char_pos += yyleng; return IGNORE; }
<*>\n           { line_num++; char_pos = 1; return IGNORE; }
.               { char_pos += yyleng; return -1;}
<S_COMMENT>"*/" { BEGIN(comment_caller); }
<S_COMMENT>"*"  { return IGNORE; }
