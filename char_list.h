#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    char value;
    long count;
    struct Node* next;
} Node;

typedef struct Header{
    Node* head;
    Node* tail;
} Header;

long* countChar(char*);
