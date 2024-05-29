#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_EOF,
    TOKEN_ID,
    TOKEN_STRING,
    TOKEN_NUMBER,
    TOKEN_PRINT,
    TOKEN_ADD,
    TOKEN_SUB,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_SEMICOLON,
    TOKEN_ERROR
} TokenType;

typedef struct {
    TokenType type;
    char *value;
} Token;

typedef struct {
    char *source;
    size_t length;
    size_t pos;
} Lexer;

Lexer *init_lexer(char *source);
Token *get_next_token(Lexer *lexer);
void free_lexer(Lexer *lexer);
void free_token(Token *token);

#endif 