#ifndef CHAR_LIST_H
#define CHAR_LIST_H

long* countChar(char*, long);

HeadNode* makeSortedLL(long*);

bool addNode(HeadNode*, TreeNode*);

Node* buildNode(TreeNode*);

Node* removeNode(Node*);

void freeNode(Node*);
#endif
