#include <stdio.h>
#include "interpreter.h"

void interpret(ASTNode *node) {
    if (!node) return;

    switch (node->type) {
        case AST_PRINT:
            interpret(node->left);
            break;
        case AST_ADD: {
            ASTNode *left = node->left;
            ASTNode *right = node->right;
            if (left->type == AST_NUMBER && right->type == AST_NUMBER) {
                int result = atoi(left->value) + atoi(right->value);
                printf("%d\n", result);
            }
            break;
        }
        case AST_SUB: {
            ASTNode *left = node->left;
            ASTNode *right = node->right;
            if (left->type == AST_NUMBER && right->type == AST_NUMBER) {
                int result = atoi(left->value) - atoi(right->value);
                printf("%d\n", result);
            }
            break;
        }
        case AST_NUMBER:
            printf("%s\n", node->value);
            break;
        case AST_STRING:
            printf("%s\n", node->value);
            break;
        default:
            break;
    }
}
