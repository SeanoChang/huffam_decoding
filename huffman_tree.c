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

TreeNode* buildHuffTree(HeadNode* hdr){
    Node* cur = hdr->head;
    Node* nex = cur->next;

    while(nex != NULL){
        TreeNode* tn = buildTreeNode('\0', cur->tnptr->count + nex->tnptr->count, 0);
        tn -> left = cur -> tnptr;
        tn -> right = nex -> tnptr;
        if(!addNode(hdr, tn)){
            fprintf(stderr, "Unable to build construct a huffman tree");
            return NULL;
        }
        cur = removeNode(cur);
        cur = removeNode(cur);
        nex = cur -> next;
        hdr->head = cur;
    }

    return hdr->head->tnptr;
}


void writeLabel(TreeNode* tn, char** label, long *pos, int* labelSize, int level){ 
    if(tn == NULL){
	    return;
    }
	if(tn->leaf == 1){
        tn->label = malloc(sizeof(char)*(level));
        tn->labelBit = level - 1;
        for(int i = 0; i < level; i++){
            tn->label[i] = (*label)[i];
        }
        return;
    }

    if(level >= *labelSize){
        char* temp = realloc(*label, sizeof(char)*(*labelSize*2));
        if(temp != NULL){
            *label = temp;
        }
        *labelSize *= 2;
    }


    (*label)[*pos] = '0';
    *pos += 1;
    writeLabel(tn -> left, label, pos, labelSize, level+1);
    *pos -= 1;
    (*label)[*pos] = '1';
    *pos += 1;
    writeLabel(tn -> right, label, pos, labelSize, level+1);
    *pos -= 1;
}

void evaluateTree(TreeNode* tn, long stringByte, char* ds, long* bit){ // decoded string
    for(int i = 0; i < stringByte; i++){
        long toAdd = 0;
        findBitSize(tn, ds[i], &toAdd);
        *bit += toAdd;
    }
}

void findBitSize(TreeNode* tn, char c, long* rtv){
    if(tn->leaf == 1){
        if(tn->value == c){
            *rtv = tn->labelBit;
            return;
        }
        return;
    } 
    findBitSize(tn -> left, c, rtv);
    findBitSize(tn -> right, c, rtv);
}

TreeNode* buildTreeNode(char value, long count, int leaf){
    TreeNode* root = malloc(sizeof(TreeNode));

    if(root != NULL){
        root -> value = value;
        root -> leaf = leaf;
        root -> count = count;
        root -> label = NULL;
        root -> labelBit = 0;
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
