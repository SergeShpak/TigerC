#include <stdlib.h>
#include <stdio.h>

#include <tokens.h>
#include <scanner_utils.h>
#include <utils.h>

int yylex(void);
extern FILE *yyin;
extern char *yytext;
extern int char_pos;
extern int line_num;

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "A file name must be provided");
    exit(1);
  }
  char *dump_file_name = "tokens.txt";
  FILE *dump_file = fopen_err(dump_file_name, "w");
  if (NULL == dump_file) {
    exit(1); 
  }
  fclose(dump_file);
  yyin = fopen_err(argv[1], "r");
  for (;;) {
    int tok = yylex();
    if (0 == tok) {
      break;
    }
    switch(tok) {
      case IGNORE:
        continue;
        break; 
      case STR_VAL:
        dump_string_to_file(dump_file_name, yylval);
        continue;
        break;
      case NUM_VAL:
        dump_num_to_file(dump_file_name, yylval);
        continue;
        break;
      case ID:
        dump_id_to_file(dump_file_name, yylval);
        continue;
        break;
      default:
        break;
    }
    if (!is_token_valid(tok)) {
      lex_token_error("", line_num, char_pos);
      continue;   
    }
    dump_token_to_file(dump_file_name, tok);
  } 
  return 0;
}
