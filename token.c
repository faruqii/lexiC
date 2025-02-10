#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    TOKEN_MATCH,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_PIPE,       // "|"
    TOKEN_ARROW,      // "=>"
    TOKEN_LBRACE,     // "{"
    TOKEN_RBRACE,     // "}"
    TOKEN_UNDERSCORE, // "_"
    TOKEN_IF,
    TOKEN_UNKNOWN,
    TOKEN_END
} TokenType;


typedef struct {
    TokenType type;
    char value[50]; // token vals
} Token;

// Lexer
#define MAX_TOKENS 100

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

        if (isalpha(input[i])) {  // Identifiers (variable names)
            j = 0;
            while (isalnum(input[i]) || input[i] == '_') {
                buffer[j++] = input[i++];
            }
            buffer[j] = '\0';

            if (strcmp(buffer, "match") == 0) add_token(TOKEN_MATCH, buffer);
            else if (strcmp(buffer, "if") == 0) add_token(TOKEN_IF, buffer);
            else add_token(TOKEN_IDENTIFIER, buffer);
        }
        else if (isdigit(input[i])) {  // Numbers
            j = 0;
            while (isdigit(input[i])) {
                buffer[j++] = input[i++];
            }
            buffer[j] = '\0';
            add_token(TOKEN_NUMBER, buffer);
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


// Parser
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
            case TOKEN_NUMBER:
            case TOKEN_UNDERSCORE:
                printf("Pattern: %s\n", token.value);
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


int main() {
    const char *code = "match x { 1 => print(\"One\"), 2 | 3 => print(\"Two or Three\"), _ => print(\"Other\") }";
    
    tokenize(code);

    printf("Tokens:\n");
    for (int i = 0; i < token_count; i++) {
        printf("{ Type: %d, Value: %s }\n", tokens[i].type, tokens[i].value);
    }

    printf("\nParsing...\n");
    parse_match();

    return 0;
}
