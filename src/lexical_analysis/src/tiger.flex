%{
#include <stdio.h>
#include <tokens.h>

int char_pos = 1;

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
%%

"var"   {return VAR;}
\n      {return 1;}
.       {return 1;}
