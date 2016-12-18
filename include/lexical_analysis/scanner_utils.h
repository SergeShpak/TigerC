#ifndef TIGER_LEX_ANALYSIS_SCANNER_UTILS_H
#define TIGER_LEX_ANALYSIS_SCANNER_UTILS_H

/**
 * \union YYSTYPE include/lexical_analysis/tokens.h
 * \brief YYSTYPE declaration used by (F)LEX.
 * 
 * YYSTYPE is the type of yylval variable in which the token value is stored
 */
typedef union {
  int pos;
  int ival;
  char *sval;
} YYSTYPE;

/** \brief Variable to store value of the processed token */
YYSTYPE yylval;


/**
 * \brief Writes a given string to the end of the file.
 *
 * Writes a given string to the end of the file.
 *
 * \param[in] file_name Destination file.
 * \param[in] str String to be written.
 *
 * \returns On success returns 0. Otherwise outputs an error message to stderr
 * and returns a value different from 0.
 */
int dump_to_file(char *file_name, char *str);

/**
 * \brief Writes a given toke to the specified file.
 *
 * Writes the given token to the specified file. Token name is resolved with
 * the use of the functions declared in include/lexical_analysis/tokens.h.
 *
 * \param[in] file_name Name of the destination file.
 * \param[in] tok Integer code of the token to be written to the file.
 *
 * \returns On success returns 0. In case of an error returns -1.
 */
int dump_token_to_file(char *file_name, int tok);

/*
 * \brief Writes the string value of the token to the file.
 *
 * Writes the token string value saved in the yylval variable to the
 * destination file.
 *
 * \param[in] file_name Name of the destination file.
 * \param[in] val Variable of the YYSTYPE to which (F)LEX writes the token
 * representation.
 *
 * \returns On success returns 0. In case of an error returns -1.
 */
int dump_string_to_file(char *file_name, YYSTYPE val);

/*
 * \brief Writes the numerical value of the token to the file.
 *
 * Writes the token numerical value saved in the yylval variable to the
 * destination file.
 *
 * \param[in] file_name Name of the destination file.
 * \param[in] val Variable of the YYSTYPE to which (F)LEX writes the token
 * representation.
 *
 * \returns On success returns 0. In case of an error returns -1.
 */
int dump_num_to_file(char *file_name, YYSTYPE val);

/*
 * \brief Writes the id token along with its value to the file.
 *
 * Writes the id token and the related string (e.g. a variable name) to the
 * given file. 
 *
 * \param[in] file_name Name of the destination file.
 * \param[in] val Variable of the YYSTYPE to which (F)LEX writes the id token
 * representation.
 *
 * \returns On success returns 0. In case of an error returns -1.
 */int dump_id_to_file(char *file_name, YYSTYPE val);

#endif
