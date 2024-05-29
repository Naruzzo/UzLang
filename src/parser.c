#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

Parser *init_parser(Lexer *lexer) {
    Parser *parser = (Parser *)malloc(sizeof(Parser));
    parser->lexer = lexer;
    parser->current_token = get_next_token(lexer);
    return parser;
}

void free_parser(Parser *parser) {
    free_token(parser->current_token);
    free(parser);
}

void free_ast(ASTNode *node) {
    if (node) {
        if (node->value) free(node->value);
        free_ast(node->left);
        free_ast(node->right);
        free(node);
    }
}

Token *consume(Parser *parser, TokenType type) {
    if (parser->current_token->type == type) {
        Token *token = parser->current_token;
        parser->current_token = get_next_token(parser->lexer);
        return token;
    }
    return NULL;
}

ASTNode *parse_number(Parser *parser) {
    Token *token = consume(parser, TOKEN_NUMBER);
    if (token) {
        ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
        node->type = AST_NUMBER;
        node->value = token->value;
        node->left = NULL;
        node->right = NULL;
        free(token);
        return node;
    }
    return NULL;
}

ASTNode *parse_string(Parser *parser) {
    Token *token = consume(parser, TOKEN_STRING);
    if (token) {
        ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
        node->type = AST_STRING;
        node->value = token->value;
        node->left = NULL;
        node->right = NULL;
        free(token);
        return node;
    }
    return NULL;
}

ASTNode *parse_expression(Parser *parser) {
    if (parser->current_token->type == TOKEN_NUMBER) {
        return parse_number(parser);
    } else if (parser->current_token->type == TOKEN_STRING) {
        return parse_string(parser);
    } else {
        return NULL;
    }
}

ASTNode *parse_print(Parser *parser) {
    consume(parser, TOKEN_PRINT);
    ASTNode *expr = parse_expression(parser);
    consume(parser, TOKEN_SEMICOLON);
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = AST_PRINT;
    node->value = NULL;
    node->left = expr;
    node->right = NULL;
    return node;
}

ASTNode *parse_add(Parser *parser) {
    consume(parser, TOKEN_ADD);
    ASTNode *left = parse_expression(parser);
    ASTNode *right = parse_expression(parser);
    consume(parser, TOKEN_SEMICOLON);
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = AST_ADD;
    node->value = NULL;
    node->left = left;
    node->right = right;
    return node;
}

ASTNode *parse_sub(Parser *parser) {
    consume(parser, TOKEN_SUB);
    ASTNode *left = parse_expression(parser);
    ASTNode *right = parse_expression(parser);
    consume(parser, TOKEN_SEMICOLON);
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = AST_SUB;
    node->value = NULL;
    node->left = left;
    node->right = right;
    return node;
}

ASTNode *parse(Parser *parser) {
    TokenType type = parser->current_token->type;

    if (type == TOKEN_PRINT) {
        return parse_print(parser);
    } else if (type == TOKEN_ADD) {
        return parse_add(parser);
    } else if (type == TOKEN_SUB) {
        return parse_sub(parser);
    } else {
        return NULL;
    }
}
