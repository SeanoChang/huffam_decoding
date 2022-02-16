#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode {
    char value;
    char count;
    bool leaf;
    char* label;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

void buildCodingTree(TreeNode*, int*, long*);



TreeNode* buildTreeNode(char, int, bool);

void destroyTree(TreeNode*);
