#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Struct.h"
#include "decode_tree.h"
#include "char_list.h"
#include "huffman_tree.h"


TreeNode* buildCodingTree(int* bp, long* pos, long terminate){
    if(bp[*pos] == 1){
        char pattern[9] = {'\0'};
        for(int i = 0; i < 8; i++){
		    if(bp[*pos+i+1] == 1){
			    pattern[i] = '1';
		    }else if(bp[*pos+i+1] == 0){
			    pattern[i] = '0';
		    }
        }
        char c = readBitToChar(pattern);
        *pos += 9;
        return buildTreeNode(c, 0, 1);
    }

    TreeNode* rtv = buildTreeNode('\0', 0, 0);
	*pos += 1;
    rtv -> left = buildCodingTree(bp, pos, terminate);
    rtv -> right = buildCodingTree(bp, pos, terminate);
    return rtv;
}

TreeNode* buildHuffTree(Node* head){
    Node* cur = head;
    Node* nex = cur -> next;

    while(nex != NULL){
        TreeNode* tn = buildTreeNode('\0', cur->tnptr->count + nex->tnptr->count, 0);
        tn -> left = cur -> tnptr;
        tn -> right = nex -> tnptr;
        if(!addNode(head, tn)){
            fprintf(stderr, "Unable to build construct a huffman tree");
            return NULL;
        }
        cur = removeNode(cur);
        cur = cur -> next;
        nex = removeNode(nex);
        nex = nex -> next;
    }

    return head->tnptr;
}


void writeLabel(TreeNode* tn, char* label, long *pos, int level){ 
    if(tn == NULL){
	    return;
    }
	if(tn->leaf == 1){
        tn->label = malloc(sizeof(char)*(level-1));
        strncpy(tn->label, label, level);
        return;
    }

    label[*pos] = '0';
    *pos += 1;
    writeLabel(tn -> left, label, pos, level+1);
    *pos -= 1;
    label[*pos] = '1';
    *pos += 1;
    writeLabel(tn -> right, label, pos, level+1);
    *pos -= 1;
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
            char* label = getLabel(&ds[i], (char)i, tn);
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


TreeNode* buildTreeNode(char value, long count, int leaf){
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

char* getLabel(char* ds, char key, TreeNode* tn){
    if(tn -> value == key){
        return tn->label;
    }

    char* label = getLabel(ds, key, tn->left);
    label = getLabel(ds,key,tn->right);

    return label;
}

void destroyTree(TreeNode* tn){
    if(tn == NULL){
        return;
    }

    destroyTree(tn -> left);
    destroyTree(tn -> right);
    free(tn -> label);
    free(tn);
}
