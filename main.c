#include <stdio.h>
#include "lexer.h"
#include "parser.h"

int main() {
    const char *code = "match x { 1 => print(\"One\"), true => print(\"True\") }";
    
    tokenize(code);

    printf("Tokens:\n");
    for (int i = 0; i < token_count; i++) {
        printf("{ Type: %d, Value: %s }\n", tokens[i].type, tokens[i].value);
    }

    printf("\nParsing...\n");
    parse_match();

    return 0;
}
