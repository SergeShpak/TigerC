#include <stdlib.h>
#include <stdio.h>

#include <tokens.h>

int yylex(void);
extern FILE *yyin;
YYSTYPE yylval;

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "A file name must be provided");
    exit(1);
  }
  yyin = fopen(argv[1], "r");
  for (;;) {
    int line_num = yylex();
    if (0 == line_num) {
      break;
    }
    printf("%d -- %s\n", line_num, yylval.sval); 
  } 
  return 0;
}
