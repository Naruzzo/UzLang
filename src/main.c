#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

void run_repl() {
    char input[256];

    printf("UzbekLang dasturiga xush kelibsiz!\n");

    while (1) {
        printf(">> ");
        if (!fgets(input, sizeof(input), stdin)) break;
        if (strncmp(input, "exit", 4) == 0) break;

        Lexer *lexer = init_lexer(input);
        Parser *parser = init_parser(lexer);
        ASTNode *root = parse(parser);

        interpret(root);

        free_ast(root);
        free_parser(parser);
        free_lexer(lexer);
    }
}

void run_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Faylni ochib bo'lmadi: %s\n", filename);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *input = (char *)malloc(length + 1);
    if (!input) {
        fprintf(stderr, "Xotirani ajratib bo'lmadi\n");
        exit(1);
    }

    fread(input, 1, length, file);
    input[length] = '\0';
    fclose(file);

    Lexer *lexer = init_lexer(input);
    Parser *parser = init_parser(lexer);
    ASTNode *root = parse(parser);

    interpret(root);

    free_ast(root);
    free_parser(parser);
    free_lexer(lexer);
    free(input);
}

int main(int argc, char **argv) {
    if (argc == 2) {
        run_file(argv[1]);
    } else {
        run_repl();
    }

    return 0;
}
