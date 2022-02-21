#ifndef DECODE_TREE_H
#define DECODE_TREE_H

/* Read the input file and interpret the 3 long values and translate each byte for the tree to an int array */
int* readBitPattern(FILE*, long* , long*, long*);

/* Read the input bit pattern and turn it into a char to store in a treenode */
char readBitToChar(char*);

/* decode the string encoded with the given coding tree */
char* decoded(FILE*, TreeNode*, long*, long, long, long, long*, int*);

/* turns a sequence of binary code and turn it into a char */
char getChar(TreeNode*, int*, long*);
#endif
