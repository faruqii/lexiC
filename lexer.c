#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"

Token tokens[MAX_TOKENS];
int token_count = 0;

void add_token(TokenType type, const char *value) {
    if (token_count < MAX_TOKENS) {
        tokens[token_count].type = type;
        strcpy(tokens[token_count].value, value);
        token_count++;
    }
}

void tokenize(const char *input) {
    char buffer[50];
    int i = 0, j = 0;

    while (input[i] != '\0') {
        if (isspace(input[i])) {
            i++;
            continue;
        }

        if (isalpha(input[i])) {  // Identifiers and keywords
            j = 0;
            while (isalnum(input[i]) || input[i] == '_') {
                buffer[j++] = input[i++];
            }
            buffer[j] = '\0';

            if (strcmp(buffer, "match") == 0) add_token(TOKEN_MATCH, buffer);
            else if (strcmp(buffer, "if") == 0) add_token(TOKEN_IF, buffer);
            else if (strcmp(buffer, "true") == 0 || strcmp(buffer, "false") == 0) add_token(TOKEN_BOOLEAN, buffer);
            else add_token(TOKEN_IDENTIFIER, buffer);
        }
        else if (isdigit(input[i])) {  // Numbers (integer)
            j = 0;
            while (isdigit(input[i])) {
                buffer[j++] = input[i++];
            }
            buffer[j] = '\0';
            add_token(TOKEN_NUMBER, buffer);
        }
        else if (input[i] == '"') {  // String literals
            i++; // skip opening quote
            j = 0;
            while (input[i] != '"' && input[i] != '\0') {
                buffer[j++] = input[i++];
            }
            buffer[j] = '\0';
            if (input[i] == '"') i++; // skip closing quote
            add_token(TOKEN_STRING, buffer);
        }
        else {  // Operators and Symbols
            switch (input[i]) {
                case '|': add_token(TOKEN_PIPE, "|"); break;
                case '{': add_token(TOKEN_LBRACE, "{"); break;
                case '}': add_token(TOKEN_RBRACE, "}"); break;
                case '_': add_token(TOKEN_UNDERSCORE, "_"); break;
                case '=':
                    if (input[i + 1] == '>') {
                        add_token(TOKEN_ARROW, "=>");
                        i++;
                    }
                    break;
                default:
                    buffer[0] = input[i];
                    buffer[1] = '\0';
                    add_token(TOKEN_UNKNOWN, buffer);
            }
            i++;
        }
    }
}
