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

TreeNode* buildHuffTree(Header* charList){
    Node* cur = charList -> head;
    Node* nex = cur -> next;

    while(nex != NULL){
        TreeNode* tn = buildTreeNode('\0', cur->tnptr->count + nex->tnptr->count, 0);
        tn -> left = cur -> tnptr;
        tn -> right = nex -> tnptr;
        cur = removeNode(cur);
        cur = cur -> next;
        nex = removeNode(nex);
        nex = nex -> next;
        if(!addNode(charList, tn)){
            fprintf(stderr, "Unable to build construct a huffman tree");
            return NULL;
        }
    }

    return charList->head;
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

void evaluateTree(TreeNode* tn, char* ds, long* byte, int* bit){ // decoded string
    char** ch = malloc(sizeof(char*)*256);
    if(ch == NULL){
        fprintf(stderr, "Unable to malloc string array for evaluation.");
        return;
    }
    for(int i = 0; i < 256; i++){
        ch[i] = malloc(sizeof(char)*8);
        if(ch[i] == NULL){
            fprintf(stderr, "Unable to malloc char array for evaluation.");
            return;
        }
        ch[i][0] = '\0';
    }

    long len = strlen(ds);

    for(int i = 0; i < len; i++){
        if(ch[(int)(ds[i])][0] != '\0'){
            byte += strlen(ch[(int)(ds[i])]);
        } else{
            char* label = getLabel(ds[i], tn);
            strncpy(ch[(int)(ds[i])], label, strlen(label));
        }
    }

    *bit = *byte % 8;
    *byte = *byte / 8;

    for(int i = 0; i < 256; i++){
        free(ch[i]);
    }

    free(ch);
}


TreeNode* buildTreeNode(char value, long count, char leaf){
    TreeNode* root = malloc(sizeof(TreeNode));
    if(root != NULL){
        root -> value = value;
        root -> leaf = leaf;
        root -> count = 0;
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