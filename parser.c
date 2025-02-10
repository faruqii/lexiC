#include <stdio.h>
#include "parser.h"
#include "lexer.h"

void parse_match() {
    if (token_count == 0) {
        printf("Error: Empty input\n");
        return;
    }

    if (tokens[0].type != TOKEN_MATCH) {
        printf("Error: Expected 'match' keyword\n");
        return;
    }

    printf("Parsing match statement...\n");

    for (int i = 1; i < token_count; i++) {
        Token token = tokens[i];

        switch (token.type) {
            case TOKEN_IDENTIFIER:
                printf("Pattern (Identifier): %s\n", token.value);
                break;
            case TOKEN_NUMBER:
                printf("Pattern (Integer): %s\n", token.value);
                break;
            case TOKEN_BOOLEAN:
                printf("Pattern (Boolean): %s\n", token.value);
                break;
            case TOKEN_STRING:
                printf("Pattern (String): %s\n", token.value);
                break;
            case TOKEN_UNDERSCORE:
                printf("Pattern: _ (Wildcard)\n");
                break;
            case TOKEN_PIPE:
                printf("Multiple patterns detected\n");
                break;
            case TOKEN_ARROW:
                printf("=> Found action mapping\n");
                break;
            case TOKEN_IF:
                printf("Guard condition detected\n");
                break;
            default:
                printf("Unknown token: %s\n", token.value);
        }
    }
}
