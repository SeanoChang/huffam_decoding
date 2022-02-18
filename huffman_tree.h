#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "decode_tree.h"
#include "char_list.h"

typedef struct TreeNode {
    char value;
    long count;
    int leaf;
    char* label;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

void buildCodingTree(TreeNode*, int*, long*);

TreeNode* buildHuffTree(Header*);

void writeLabel(TreeNode*, char*, long*, int);

TreeNode* buildTreeNode(char, long, char);

void destroyTree(TreeNode*);
