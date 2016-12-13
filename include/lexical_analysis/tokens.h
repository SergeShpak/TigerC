#ifndef TIGER_LEX_ANALYSIS_TOKENS_H
#define TIGER_LEX_ANALYSIS_TOKENS_H

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
extern YYSTYPE yylval;

#define VAR       257
#define UNKNOWN   258

#endif
