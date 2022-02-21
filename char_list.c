#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Struct.h"
#include "char_list.h"
#include "huffman_tree.h"

long* countChar(char* dString, long len){
    long* count = malloc(sizeof(long) * 256);

    for(int i = 0; i < 256; i++){
        count[i] = 0;
    }

    for(int i = 0; i < len; i++){
        int c = (int)(dString[i]);
        count[c]++;
    }

    return count;
}

HeadNode* makeSortedLL(long * charCount){
    HeadNode* header = malloc(sizeof(HeadNode));
    header -> head = NULL;
    for(int i =0; i < 256; i++){
        if(charCount[i] > 0){
            if(!addNode(header, buildTreeNode((char)(i), charCount[i], 1))){
                fprintf(stderr, "Cannot add node and build tree.");
                return NULL;
            }
        }
    }

   return header;
}

bool addNode(HeadNode* hdr, TreeNode * tn){
	if(hdr -> head == NULL){
		Node * node = buildNode(tn);
		hdr -> head = node;
		return true;
	}

	Node* cur = hdr -> head; //current position
	Node* nex = cur -> next; //next to current position

    while(nex != NULL){
        if(tn->count < cur->tnptr->count){
            TreeNode* temp = cur -> tnptr;
            Node* node = buildNode(temp);
            cur -> tnptr = tn;
            cur -> next = node;
            node -> next = nex;
            return true;
        }
        cur = cur -> next;
        nex = nex -> next;
    }
   
	if(tn->count < cur->tnptr->count){
        TreeNode* temp = cur->tnptr;
		Node* node = buildNode(temp);
        cur->tnptr = tn;
        cur->next = node;
		return true;
	}

	Node * node = buildNode(tn);
	cur->next = node;
	return true;
}

Node* buildNode(TreeNode * tn){
   Node * nd = malloc(sizeof(Node));
   nd -> tnptr = tn;
   nd -> next = NULL;
   return nd;
}

Node* removeNode(Node* nd){
    Node* temp = nd;
    nd = nd -> next;
    free(temp);

    return nd;
}

void freeNode(Node* head){
    while(head != NULL){
        Node* temp = head;
        head = head -> next;
        free(temp);
    }

    free(head);
}
