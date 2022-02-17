#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "huffman_tree.h"

void buildCodingTree(TreeNode* root, int* bp, long* pos){
    if(bp[*pos] == 1){
        int pattern[8];
        for(int i = 0; i < 8; i++){
            pattern[i] = bp[*pos+1+i];
        }
        char c = readBitToChar(pattern);
        *pos += 9;
        root = buildTreeNode(c, 0, '1');
        return;
    }

    if(root == NULL){
        root = buildTreeNode('\0', 0, '0');
    }
    buildCodingTree(root->left, bp, pos);
    buildCodingTree(root->right, bp, pos);
}

void writeLabel(TreeNode* tn, char* label, long *pos, int level){ 
    if(tn->leaf == '1'){
        tn->label = malloc(sizeof(char)*level);
        strncpy(tn->label, label, level);
        return;
    }

    label[*pos] = '0';
    writeLabel(tn -> left, label, *pos, level+1);
    label[*pos] = '1';
    writeLabel(tn -> right, label, *pos, level+1);
}

TreeNode* buildTreeNode(char value, int count, char leaf){
    TreeNode* root = malloc(sizeof(TreeNode));
    if(root != NULL){
        root -> value = value;
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
