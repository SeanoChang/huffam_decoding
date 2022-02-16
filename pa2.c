#include <stdio.h>
#include <stdlib.h>

#include "huffman_tree.h"
#include "decode_tree.h"
#include "char_list.h"


int main(int argc, char** argv){
    if(argc != 7){
        fprintf(stderr, "Incorrect input files number");
        return EXIT_FAILURE;
    }

    long totalByte; // the total bytes in the file
    long treeByte; // the bytes to be read for the coding tree
    long stringByte; // the bytes of the original string
    int* bitPatterns = readBitPattern(argv[1], &totalByte, &treeByte, &stringByte); // get the bit patterns for building the tree

    TreeNode* rTree = NULL; // reconstructed tree from the input file
    long pos = 0; // the position for bit pattern array
    buildCodingTree(rTree, bitPatterns, &pos);
    if(writeOutput1(argv[2], rTree) == false){
        fprintf(stderr, "Unable to write the tree file");
        return EXIT_FAILURE;
    }

    writeLabel(rTree);
    char* dString = decoded(argv[1], rTree); // decoded string 
    if(writeOutput2(argv[3], dString) == false){
        fprintf(stderr, "Unable to write the ori file");
        return EXIT_FAILURE;
    }

    long* characters = countChar(dString); // count each acsii characters 
    if(writeOutput3(argv[4], characters) == false){
        fpritnf(stderr, "Unable to write the count file.");
        return EXIT_FAILURE;
    }

    TreeNode* hTree = NULL; // the huffman tree to be encoded
    buildHuffTree(hTree, characters);
    if(writeOutput4(argv[5], hTree) == false){
        fprintf(stderr, "Unable to wirte the htree file.");
        return EXIT_FAILURE;
    }

    writeLabel(hTree);
    if(writeOutput5(argv[6], hTree) == false){
        fprintf(stderr, "Unable to write the eval file.");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
