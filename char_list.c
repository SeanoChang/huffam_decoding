#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman_tree.h"

long* countChar(char* dString){
    long* count = malloc(sizeof(long) * 256);

    for(int i = 0; i < 256; i++){
        count[i] = 0;
    }

    long len = strlen(dString);

    for(int i = 0; i < len; i++){
        int c = (int)(dString[i]);
        count[c]++;
    }

    return count;
}

Header* makeSortedLL(long * charCount){
    Header* hdr = malloc(sizeof(Header));
    if(hdr == NULL){
        fprintf(stderr, "Unable to initialize header for char linked list.");
        return NULL;
    }
    hdr->head = NULL;
    hdr->tail = NULL;
    for(int i =0; i < 256; i++){
        if(charCount[i] > 0){
            if(!addNode(hdr, buildTreeNode((char)(i), charCount[i], '1'))){
                fprintf(stderr, "Cannot add node and build tree.");
                return NULL;
            }
        }
    }

   return hdr;
}

bool addNode(Header* hdr, TreeNode * tn){
	if(hdr -> head == NULL){
		Node * node = buildNode(tn);
		hdr -> head -> tnptr = node;
        hdr -> tail -> tnptr = node;
		return true;
	}

	Node* cur = hdr -> head; //current position
	Node* nex = hdr -> head -> next; //next to current position
	while(nex != NULL){
		if(tn->count < cur->tnptr->count){
            TreeNode * temp = cur->tnptr;
			Node * node = buildNode(temp);
            cur -> tnptr = tn;
			cur -> next = node;
			node -> next = nex;
			return true;
		}
		cur = cur -> next;
		nex = nex -> next;
	}

	if(tn->count < cur->tnptr->count){
        TreeNode * temp = cur->tnptr;
	    Node * node = buildNode(temp);
        cur->tnptr = tn;
        cur->next = node;
		return true;
	}

    hdr->tail = cur;
   
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

void freeNode(Node* head){
    while(head != NULL){
        Node* temp = head;
        head = head -> next;
        free(temp);
    }

    free(head);
}
