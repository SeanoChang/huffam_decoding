#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

/* reconstruct the original coding tree */
TreeNode* buildCodingTree(int*, long*,long);

/* build huffman tree */
TreeNode* buildHuffTree(HeadNode*);

/* write label according to the coding tree */
void writeLabel(TreeNode*, char**, long*, int);

TreeNode* buildTreeNode(char, long, int);

/* evaluate the huffman tree for the eval output */
void evaluateTree(TreeNode*, long, char*, long*);

/* find the bit size for each label */
void findBitSize(TreeNode*, char, long*);

/* get the label for a specific character */
char* getLabel(char*, char, TreeNode*);

void destroyTree(TreeNode*);

#endif
