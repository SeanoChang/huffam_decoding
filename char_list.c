#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Struct.h"
#include "char_list.h"
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

Node* makeSortedLL(long * charCount){
    Node* head = NULL;
    for(int i =0; i < 256; i++){
        if(charCount[i] > 0){
            if(!addNode(head, buildTreeNode((char)(i), charCount[i], 1))){
                fprintf(stderr, "Cannot add node and build tree.");
                return NULL;
            }
        }
    }

   return head;
}

bool addNode(Node* head, TreeNode * tn){
	if(head == NULL){
		Node * node = buildNode(tn);
		head = node;
		return true;
	}

	Node* cur = head; //current position
	Node* nex = cur -> next; //next to current position
	if(nex == NULL){
        Node* node = buildNode(tn);
        if(tn -> count < cur -> tnptr -> count){
            head = node;
            node -> next = cur;
        } else if(tn -> count == cur -> tnptr -> count && (int)(tn->value) < (int)(cur->tnptr->value)){
            head = node;
            node -> next = cur;
        } else {
            cur -> next = node;
        }
        return true;
    }

    while(nex != NULL){
        if(tn -> count < cur -> tnptr -> count){
            Node* node = buildNode(tn);
            cur -> next = node;
            node -> next = nex;
            return true;
        }
        cur = cur -> next;
        nex = nex -> next;
    }
   
   if(tn -> count < cur -> tnptr -> count){
        Node* node = buildNode(tn);
        cur -> next = node;
        node -> next = nex;
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
