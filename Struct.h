#ifndef STRUCT_H
#define STRUCT_H

typedef struct TreeNode {
    char value;
    long count;
    int leaf;
    char* label;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct Node{
    TreeNode* tnptr;
    struct Node* next;
} Node;

typedef struct Header{
    Node* head;
    Node* tail;
} Header;
#endif
