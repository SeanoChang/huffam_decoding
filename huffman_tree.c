#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "huffman_tree.h"
#include "decode_tree.h"

void buildCodingTree(TreeNode* root, int* bp, long* pos){
    if(bp[*pos] == 1){
        int pattern[8];
        for(int i = 0; i < 8; i++){
            pattern[i] = bp[*pos+1+i];
        }
        char c = readBitToChar(pattern);
        *pos += 9;
        root = buildTreeNode(c, 0, true);
        return;
    }

    if(root == NULL){
        root = buildTreeNode('\0', 0, false);
    }
    buildCodingTree(root->left, bp, pos);
    buildCodingTree(root->right, bp, pos);
}

TreeNode* buildTreeNode(char value, int count, bool leaf){
    TreeNode* root = malloc(sizeof(TreeNode));
    if(root != NULL){
        root -> value = value;
        root -> count = count;
        root -> leaf = leaf;
        root -> label = NULL;
        root -> left = NULL;
        root -> right = NULL;
    }
    return root;
}

void destroyTree(TreeNode* tn){
    if(tn == NULL){
        return;
    }

    destroyTree(tn -> left);
    destroyTree(tn -> right);
    free(tn);
}
