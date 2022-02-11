#include <stdio.h>
#include <stdlib.h>

#include "huffman_tree.h"

TreeNode* buildHuffmanTree(TreeNode*);

TreeNode* buildTreeNode(char value, int count){
    TreeNode* root = malloc(sizeof(TreeNode));
    if(root != NULL){
        root -> value = value;
        root -> count = count;
        root -> left = NULL;
        root -> right = NULL;
    }
    return root;
}

void destroyTree(TreeNode* tn){
    if(tn == NULL){
        return;
    }

    freeTree(tn -> left);
    freeTree(tn -> right);
    free(tn);
}