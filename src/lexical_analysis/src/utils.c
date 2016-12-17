#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <utils.h>
#include <tokens.h>
#include <scanner_utils.h>



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
  char *msg = insert_into_string(msg_template, file);
  lex_error(msg);
  free(msg);
  msg = NULL;
  return result;
}

char *insert_into_string(char *result_template, char *str) {
  size_t msg_size = strlen(result_template) + strlen(str);
  char *msg = (char*) malloc(sizeof(char) * (msg_size + 1));
  if (NULL == msg) {
    return NULL;
  }
  sprintf(msg, result_template, str);
  return msg; 
}
