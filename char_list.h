#ifndef CHAR_LIST_H
#define CHAR_LIST_H

/* count ascii characters */
long* countChar(char*, long);

/* make sorted linked list that contains a pointer pointing to a treenode that contains all the information needed */
HeadNode* makeSortedLL(long*);

/* the helper function for making the link list in order */
bool addNode(HeadNode*, TreeNode*);

Node* buildNode(TreeNode*);

Node* removeNode(Node*);

void freeNode(Node*);
#endif
