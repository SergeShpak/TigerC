#ifndef TIGER_LEX_ANALYSIS_TOKENS_H
#define TIGER_LEX_ANALYSIS_TOKENS_H

const char * const get_token_string(int token);
int is_token_valid(int token);

// token values returned by the scanner
#define STRING    257
#define INT       258
#define COMMA     259
#define SEMICOLON 260
#define COLON     261
#define LPAREN    262
#define RPAREN    263
#define LBRACE    264
#define RBRACE    265
#define DOT       266
#define PLUS      267
#define MINUS     268
#define TIMES     269
#define DIVIDE    270
#define EQ        271
#define NEQ       272
#define LT        273
#define LE        274
#define GT        275
#define GE        276
#define AND       277
#define OR        278
#define ASSIGN    279
#define ARRAY     280
#define IF        281
#define THEN      282
#define ELSE      283
#define WHILE     284
#define FOR       285
#define TO        286
#define DO        287
#define LET       288
#define IN        289
#define END       290
#define OF        291
#define BREAK     292
#define NIL       293
#define FUNCTION  294
#define VAR       295
#define TYPE      296
#define ID        297
#define LBRACK    298
#define RBRACK    299
#define IGNORE    300

#endif
