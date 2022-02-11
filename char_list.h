#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    char value;
    long count;
    Node* next;
} Node;

Node* buildList(char, int);

void freeList(Node*);