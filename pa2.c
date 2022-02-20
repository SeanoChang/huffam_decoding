#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Struct.h"
#include "huffman_tree.h"
#include "write_output.h"
#include "char_list.h"
#include "decode_tree.h"

int main(int argc, char** argv){
    if(argc != 7){
        fprintf(stderr, "Incorrect input files number");
        return EXIT_FAILURE;
    }

    //open input file
    FILE* fp = fopen(argv[1], "rb"); 
    if(fp == NULL){
        fclose(fp);
        fprintf(stderr, "Cannot open input file for reading!");
        return EXIT_FAILURE;
    }

    long totalByte; // the total bytes in the file
    long treeByte; // the bytes to be read for the coding tree
    long stringByte; // the bytes of the original string
    int* bitPatterns = readBitPattern(fp, &totalByte, &treeByte, &stringByte); // get the bit patterns for building the tree

    TreeNode* rTree = NULL; // reconstructed tree from the input file
    long pos = 0; // the position for writing bit pattern array
    buildCodingTree(rTree, bitPatterns, &pos);

    if(writeOutput1(argv[2], rTree) == false){
        fprintf(stderr, "Unable to write the tree file");
        return EXIT_FAILURE;
    }

    pos = 0;
    char* label = malloc(sizeof(char) * 8);
    char* dString = malloc(sizeof(char)); // decoded string if the size if not enough, then realloc size
    long rByte = 0; // the bytes needed for writing the string with the original coding tree
    int rBit = 0; // the remaining bits needed for writing the string with the original coding tree
    writeLabel(rTree, label, &pos, 1);
    long decodeByte = decoded(fp, rTree, dString, totalByte, treeByte, stringByte, &rByte, &rBit); // decoded string, file closes here
fprintf(stdout,"%ld %ld\n", decodeByte, stringByte);     
if(decodeByte != stringByte){
        fprintf(stderr, "Unable to decode the original string.");
        return EXIT_FAILURE;
    }
    if(writeOutput2(argv[3], dString) == false){
        fprintf(stderr, "Unable to write the ori file");
        return EXIT_FAILURE;
    }
    destroyTree(rTree); // destroy reconstructed tree after using 


    long* characters = countChar(dString); // count each acsii characters 
    if(writeOutput3(argv[4], characters) == false){
        fprintf(stderr, "Unable to write the count file.");
        return EXIT_FAILURE;
    }

    pos = 0;
    Header* header = makeSortedLL(characters); // linked list for building huffman tree
    TreeNode* hTree = buildHuffTree(header); // the huffman tree to be encoded
    writeLabel(hTree, label, &pos, 1);
    free(label); // free  label after using
    if(writeOutput4(argv[5], hTree) == false){
        fprintf(stderr, "Unable to wirte the htree file.");
        return EXIT_FAILURE;
    }

    long hByte = 0;
    int hBit = 0;
    evaluateTree(hTree, dString, &hByte, &hBit);
    if(writeOutput5(argv[6], rByte, rBit, hByte, hBit) == false){
        fprintf(stderr, "Unable to write the eval file.");
        return EXIT_FAILURE;
    }
	fclose(fp);
    destroyTree(hTree);
    free(dString);

    return EXIT_SUCCESS;
}
