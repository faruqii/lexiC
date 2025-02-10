#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_MATCH,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,       // Integer numbers
    TOKEN_BOOLEAN,      // Boolean literals
    TOKEN_STRING,       // String literals
    TOKEN_PIPE,         // "|"
    TOKEN_ARROW,        // "=>"
    TOKEN_LBRACE,       // "{"
    TOKEN_RBRACE,       // "}"
    TOKEN_UNDERSCORE,   // "_"
    TOKEN_IF,
    TOKEN_UNKNOWN,
    TOKEN_END
} TokenType;

typedef struct {
    TokenType type;
    char value[50]; // token values
} Token;

#endif // TOKEN_H
