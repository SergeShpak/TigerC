#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <tokens.h>
#include <scanner_utils.h>
#include <utils.h>

/**
 * Returns a heap-allocated message that can contain the passed file name.
 */
static char *get_file_error_message(char *msg_template, char *file_name);
static size_t number_of_symb(int num);

// TODO: finish status checking
int dump_token_to_file(char *file_name, int token) {
  const char * const token_str = get_token_string(token);
  size_t token_str_len = strlen(token_str);
  char *token_repr = (char *) malloc(sizeof(char) * (token_str_len + 1));
  if (NULL == token_repr) {
    return -1; 
  }
  sprintf(token_repr, "%s ", token_str);
  dump_to_file(file_name, token_repr);
  free(token_repr);
  return -1;
}

int dump_string_to_file(char *file_name, YYSTYPE val) {
  char *text = val.sval;
  size_t str_len = strlen(text);
  char *str_repr = (char*) malloc(sizeof(char) * (str_len + 1));
  sprintf(str_repr, "STRVAL %%%s%% ", text);
  dump_to_file(file_name, str_repr);
  free(str_repr);
  return -1;
}

int dump_num_to_file(char *file_name, YYSTYPE val) {
  int num = yylval.ival;
  size_t num_of_digits = number_of_symb(num);
  char *digit_repr = (char*) malloc(sizeof(char) * (num_of_digits + 5));
  sprintf(digit_repr, "NUM %%%d%% ", num);
  dump_to_file(file_name, digit_repr);
  free(digit_repr);
  return -1;
}

int dump_id_to_file(char *file_name, YYSTYPE val) {
  char *name = yylval.sval; 
  size_t str_len = strlen(name);
  char *id_repr = (char*) malloc(sizeof(char) * (str_len + 4));
  sprintf(id_repr, "ID %s ", name);
  dump_to_file(file_name, id_repr);
  free(id_repr);
  return -1;
}

int dump_to_file(char *file_name, char *str) {
  int status = -1;
  FILE *file = fopen_err(file_name, "a+");
  if (NULL == file) {
    return 0;
  }
  int write_res = lex_log(str, file);
  if (write_res) {
    status = 0;
    char *msg_template = "Could not write to %s";
    char *err_msg = insert_into_string(msg_template, file_name);
    lex_error(err_msg);
    free(err_msg);
  }
  fclose(file);
  return status;
}

/******************************************************************************
 * Static functions
 * ***************************************************************************/

size_t number_of_symb(int num) {
  size_t len = 0;
  if (0 == num) {
    return num; 
  }
  int curr_num = num;
  while(0 != curr_num) {
    curr_num /= 10;
    len++; 
  }
  return len;
}

/******************************************************************************
 * End of static functions section
 * ***************************************************************************/
