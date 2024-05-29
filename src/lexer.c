#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"

Lexer *init_lexer(char *source) {
    Lexer *lexer = (Lexer *)malloc(sizeof(Lexer));
    lexer->source = source;
    lexer->length = strlen(source);
    lexer->pos = 0;
    return lexer;
}

void free_lexer(Lexer *lexer) {
    free(lexer);
}

Token *create_token(TokenType type, char *value) {
    Token *token = (Token *)malloc(sizeof(Token));
    token->type = type;
    token->value = value;
    return token;
}

void free_token(Token *token) {
    if (token->value) free(token->value);
    free(token);
}

char peek(Lexer *lexer) {
    if (lexer->pos < lexer->length) {
        return lexer->source[lexer->pos];
    }
    return '\0';
}

char advance(Lexer *lexer) {
    lexer->pos++;
    return peek(lexer);
}

void skip_whitespace(Lexer *lexer) {
    while (isspace(peek(lexer))) {
        advance(lexer);
    }
}

Token *get_next_token(Lexer *lexer) {
    skip_whitespace(lexer);

    char current = peek(lexer);

    if (current == '\0') {
        return create_token(TOKEN_EOF, NULL);
    }

    if (isalpha(current)) {
        size_t start = lexer->pos;
        while (isalpha(peek(lexer))) advance(lexer);

        size_t length = lexer->pos - start;
        char *value = (char *)malloc(length + 1);
        strncpy(value, lexer->source + start, length);
        value[length] = '\0';

        if (strcmp(value, "Yoz") == 0) return create_token(TOKEN_PRINT, value);
        if (strcmp(value, "Qosh") == 0) return create_token(TOKEN_ADD, value);
        if (strcmp(value, "Ayir") == 0) return create_token(TOKEN_SUB, value);

        return create_token(TOKEN_ID, value);
    }

    if (isdigit(current)) {
        size_t start = lexer->pos;
        while (isdigit(peek(lexer))) advance(lexer);

        size_t length = lexer->pos - start;
        char *value = (char *)malloc(length + 1);
        strncpy(value, lexer->source + start, length);
        value[length] = '\0';

        return create_token(TOKEN_NUMBER, value);
    }

    if (current == '\"') {
        advance(lexer); // Skip the opening quote
        size_t start = lexer->pos;

        while (peek(lexer) != '\"' && peek(lexer) != '\0') advance(lexer);

        size_t length = lexer->pos - start;
        char *value = (char *)malloc(length + 1);
        strncpy(value, lexer->source + start, length);
        value[length] = '\0';

        advance(lexer); // Skip the closing quote

        return create_token(TOKEN_STRING, value);
    }

    if (current == '(') {
        advance(lexer);
        return create_token(TOKEN_LPAREN, strdup("("));
    }

    if (current == ')') {
        advance(lexer);
        return create_token(TOKEN_RPAREN, strdup(")"));
    }

    if (current == ';') {
        advance(lexer);
        return create_token(TOKEN_SEMICOLON, strdup(";"));
    }

    return create_token(TOKEN_ERROR, NULL);
}
