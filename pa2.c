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
        fprintf(stderr, "Incorrect input files number.\n");
        return EXIT_FAILURE;
    }

    //open input file
    FILE* fp = fopen(argv[1], "rb"); 
    if(fp == NULL){
        fclose(fp);
        fprintf(stderr, "Cannot open input file for reading!\n");
        return EXIT_FAILURE;
    }

    long totalByte; // the total bytes in the file
    long treeByte; // the bytes to be read for the coding tree
    long stringByte; // the bytes of the original string
    int* bitPatterns = readBitPattern(fp, &totalByte, &treeByte, &stringByte); // get the bit patterns for building the tree

    long pos = 0; // the position for writing bit pattern array
    TreeNode* rTree = buildCodingTree(bitPatterns, &pos, treeByte);// reconstructed tree from the input file

    /* write output 1 */
    if(writeOutput1(argv[2], rTree) == false){
        fprintf(stderr, "Unable to write the tree file.\n");
        return EXIT_FAILURE;
    }

    pos = 0;
    char* label = malloc(sizeof(char) * 9); // temp location for storing characters' coding tree label
    for(int i = 0; i < 9; i++) {
        label[i] = '\0';
    }

    long rByte = 0; // the bytes needed for writing the string with the original coding tree
    int rBit = 0; // the remaining bits needed for writing the string with the original coding tree

    /* write label for each leaf node */
    writeLabel(rTree, &label, &pos, 1);

    long strLen = 0; // length of the decoded string
    char* dString = decoded(fp, rTree, &strLen, totalByte, treeByte, stringByte, &rByte, &rBit); // get decoded string, file closes here
    if(dString == NULL) {
        fprintf(stderr, "Unable to decode the string.\n");
        return EXIT_FAILURE;
    }

    /* write output 2 */
    if(writeOutput2(argv[3], dString, strLen) == false){
        fprintf(stderr, "Unable to write the ori file.\n");
        return EXIT_FAILURE;
    }

    long* characters = countChar(dString, stringByte); // count each acsii characters 

     /* output the count for each ascii characters */
    if(writeOutput3(argv[4], characters) == false){
        fprintf(stderr, "Unable to write the count file.\n");
        return EXIT_FAILURE;
    }

    /* build the new huffman tree */
    pos = 0; 
    HeadNode* header = makeSortedLL(characters); // header points to the linked list for building huffman tree
    TreeNode* hTree = buildHuffTree(header); // the huffman tree to be encoded
    for(int i = 0; i < 9; i++) {
        label[i] = '\0';
    }
    writeLabel(hTree, &label, &pos, 1);
    

    /* write output 4 */
    if(writeOutput4(argv[5], hTree) == false){
        fprintf(stderr, "Unable to wirte the htree file.\n");
        return EXIT_FAILURE;
    }

    /* return the total bit needed for the wrtiting string with the huffman tree to hTreeBit */
    long hTreeBit = 0;
    evaluateTree(hTree, stringByte, dString, &hTreeBit); 

    /* write output 5 */
    if(writeOutput5(argv[6], rByte, rBit, hTreeBit) == false){
        fprintf(stderr, "Unable to write the eval file.\n");
        return EXIT_FAILURE;
    }

    /* free all malloc */
    free(header->head);
    free(header);
    free(bitPatterns);
    free(characters);
    free(label);
    destroyTree(rTree); 
    destroyTree(hTree);
    free(dString);

    return EXIT_SUCCESS;
}
