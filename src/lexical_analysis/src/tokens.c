const char * const get_token_string(int token) {
  static const char * const tokens_names[] = 
                    { "STRING", "INT", "COMMA", "SEMICOLON", "COLON", 
                      "LPAREN", "RPAREN", "LBRACE", "RBRACE", "DOT", "PLUS", 
                      "MINUS", "TIMES", "DIVIDE", "EQ", "NEQ", "LT", "LE", 
                      "GT", "GE", "AND", "OR", "ASSIGN", "ARRAY", "IF", "THEN", 
                      "ELSE", "WHILE", "FOR", "TO", "DO", "LET", "IN", "END", 
                      "OF", "BREAK", "NIL", "FUNCTION", "VAR", "TYPE", "ID", 
                      "LBRACK", "RBRACK" };

  return tokens_names[token - 257];
}

int is_token_valid(int token) {
  return token >= 257 && token <= 300;
}
