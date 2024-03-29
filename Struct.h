#ifndef STRUCT_H
#define STRUCT_H

typedef struct TreeNode {
    char value;
    long count;
    int leaf;
    char* label;
    int labelBit;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct Node{
    TreeNode* tnptr;
    struct Node* next;
} Node;

typedef struct HeadNode{
    Node* head;
} HeadNode;
#endif
