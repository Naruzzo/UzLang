#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef enum {
    AST_PRINT,
    AST_ADD,
    AST_SUB,
    AST_NUMBER,
    AST_STRING
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    char *value;
    struct ASTNode *left;
    struct ASTNode *right;
} ASTNode;

typedef struct {
    Lexer *lexer;
    Token *current_token;
} Parser;

Parser *init_parser(Lexer *lexer);
ASTNode *parse(Parser *parser);
void free_parser(Parser *parser);
void free_ast(ASTNode *node);

#endif 
