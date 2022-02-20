#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

void buildCodingTree(TreeNode*, int*, long*);

TreeNode* buildHuffTree(Header*);

void writeLabel(TreeNode*, char*, long*, int);

TreeNode* buildTreeNode(char, long, int);

void evaluateTree(TreeNode*, char*, long*, int*);

char* getLabel(char*, char, TreeNode*);

void destroyTree(TreeNode*);

#endif
