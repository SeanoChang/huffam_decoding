#ifndef WRITE_OUTPUT_H
#define WRITE_OUTPUT_H

/* 
argv[2] the first output is topology information of the tree (pre-order)
argv[3] the second output is the decoded file 
argv[4] the third output is the count for each ASCII characters (256 * sizeof(long))
argv[5] the fourth output is the topology information of the constructed huffman coding tree
argv[6] the fifth output contains a pair of numbers together specify the number of bits required by the coding tree 
in the input file to encode the original file and a second pair of numbers together specify the number of bits 
required by the Huffman coding tree to encode the original file. 
*/

bool writeOutput1(char*, TreeNode*);

bool writeOutput2(char*, char*, long);

bool writeOutput3(char*, long*);

bool writeOutput4(char*, TreeNode*);

bool writeOutput5(char*, long, int, long);
#endif
