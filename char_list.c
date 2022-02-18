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
	if(nex == NULL){
        Node* node = buildNode(tn);
        if(tn -> count < cur -> tnptr -> count){
            hdr -> head = node;
            node -> next = cur;
        } else if(tn -> count == cur -> tnptr -> count && (int)(tn->value) < (int)(cur->tnptr->value)){
            hdr -> head = node;
            node -> next = cur;
        } else {
            cur -> next = node;
            hdr -> tail = node;
        }
        return true;
    }

    while(nex != NULL && tn->count <= nex->tnptr->count){
        if(tn -> count == cur -> tnptr -> count && (int)(tn->value) > (int)(cur->tnptr->value)){
            Node* node = buildNode(tn);
            cur -> next = node;
            node -> next = nex;
            if(nex == NULL) hdr -> tail = node;
            return true;
        }
        cur = cur -> next;
        nex = nex -> next;
    }
   
	Node * node = buildNode(tn);
	cur->next = node;
    node->next = nex;
    if(nex == NULL) hdr -> tail = node;
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
