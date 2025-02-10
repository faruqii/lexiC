#ifndef LEXER_H
#define LEXER_H

#include "token.h"

#define MAX_TOKENS 100

extern Token tokens[MAX_TOKENS];
extern int token_count;

void add_token(TokenType type, const char *value);
void tokenize(const char *input);

#endif // LEXER_H
