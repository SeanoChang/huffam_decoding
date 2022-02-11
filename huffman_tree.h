#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    char value;
    long count;
    TreeNode* left;
    TreeNode* right;
} TreeNode;

TreeNode* buildHuffmanTree(TreeNode*);

TreeNode* buildTreeNode(char, int);

void destroyTree(TreeNode*);