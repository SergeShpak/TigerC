#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <utils.h>
#include <tokens.h>

/**
 * Returns a heap-allocated message that can contain the passed file name.
 */
static char *get_file_error_message(char *msg_template, char *file_name);

int lex_error(char *msg) {
  int res = fprintf(stderr, "ERROR: %s\n", msg);
  if (res >= 0) {
    return 0;
  }
  return -1;
}

// TODO: add all necessary checkings
int lex_token_error(char *explanation, int line_num, int char_pos) {
  int status = 0;
  //11 = number of characters to represent 2^32 + 1 (for the terminating zero) 
  char *str_line_num = (char*) malloc(sizeof(char) * 11);
  char *str_char_pos = (char*) malloc(sizeof(char) * 11);
  if (NULL == str_line_num || NULL == str_char_pos) {
    lex_error("Malloc failed");
  }
  sprintf(str_line_num, "%d", line_num);
  sprintf(str_char_pos, "%d", char_pos);
  char *msg_template = "Bad token at: %s:%s: %s";
  size_t msg_str_len = strlen(str_line_num) + strlen(str_char_pos) 
                        + strlen(explanation) + (strlen(msg_template) - 6) + 1;
  char *msg = (char*) malloc(sizeof(char) * msg_str_len);
  sprintf(msg, msg_template, str_line_num, str_char_pos, explanation);
  lex_error(msg);
  free(str_line_num);
  free(str_char_pos);
  free(msg);
  return status;
}

int lex_log(char *msg, FILE* f) {
  int res = fprintf(f, "%s", msg);
  if (res >= 0) {
    return 0; 
  }
  return -1;
}

FILE *fopen_err(char *file, char *mode) {
  FILE *result = fopen(file, mode);
  if (NULL != result) {
    return result;
  }

  /* The part where we display the error message */
  char *msg_template = "File %s cannot be opened.";
  char *msg = get_file_error_message(msg_template, file);
  lex_error(msg);
  free(msg);
  msg = NULL;
  return result;
}

int dump_token_to_file(char *file_name, int token) {
  const char * const token_str = get_token_string(token);
  size_t token_str_len = strlen(token_str);
  char *token_repr = (char *) malloc(sizeof(char) * (token_str_len + 2));
  sprintf(token_repr, "%s ", token_str);
  dump_to_file(file_name, token_repr);
  free(token_repr);
  return 0;
}

int dump_to_file(char *file_name, char *str) {
  int status = 0;
  FILE *file = fopen_err(file_name, "a+");
  if (NULL == file) {
    return 1;
  }
  int write_res = lex_log(str, file);
  if (write_res) {
    status = 1;
    char *msg_template = "Could not write to %s";
    char *err_msg = get_file_error_message(msg_template, file_name);
    lex_error(err_msg);
    free(err_msg);
  }
  fclose(file);
  return status;
}

/******************************************************************************
 * Static functions
 * ***************************************************************************/

char *get_file_error_message(char *msg_template, char *file_name) {
  size_t msg_size = strlen(msg_template) + strlen(file_name);
  char *msg = (char*) malloc(sizeof(char) * (msg_size + 1));
  sprintf(msg, msg_template, file_name);
  return msg;
}

/******************************************************************************
 * End of static functions section
 * ***************************************************************************/
