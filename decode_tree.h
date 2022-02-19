#ifndef DECODE_TREE_H
#define DECODE_TREE_H

int* readBitPattern(FILE*, long* , long*, long*);
/*
Read the input file and interpret the 3 long values and translate each byte for the tree to an int array 
*/

char readBitToChar(int*);
/*
Read the input bit pattern and turn it into a char to store in a treenode
*/

long decoded(FILE*, TreeNode*, char*, long, long, long, long*, int*);

char getChar(TreeNode*, int*, long*);
#endif
