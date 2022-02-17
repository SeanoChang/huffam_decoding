#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node{
    TreeNode* tnptr;
    struct Node* next;
} Node;

typedef struct Header{
    Node* head;
    Node* tail;
} Header;

long* countChar(char*);

Header* makeSortedLL(long*);

bool addNode(Header*, TreeNode*);

Node* buildNode(TreeNode*);

void freeNode(Node*);
