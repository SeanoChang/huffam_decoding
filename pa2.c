#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Struct.h"
#include "huffman_tree.h"
#include "write_output.h"
#include "char_list.h"
#include "decode_tree.h"

void printPre(TreeNode* tn){
    if(tn == NULL){
        return;
    }

    printf("%d", tn->leaf);
    if(tn -> leaf == 1){
        printf("%c\n", tn->value);
        printf("this is label: %s\n", tn->label);
    }
    printPre(tn->left);
    printPre(tn->right);
}

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

    long pos = 0; // the position for writing bit pattern array
    TreeNode* rTree = buildCodingTree(bitPatterns, &pos, treeByte);// reconstructed tree from the input file

    if(writeOutput1(argv[2], rTree) == false){
        fprintf(stderr, "Unable to write the tree file");
        return EXIT_FAILURE;
    }

    pos = 0;
    char* label = malloc(sizeof(char) * 8);
    long rByte = 0; // the bytes needed for writing the string with the original coding tree
    int rBit = 0; // the remaining bits needed for writing the string with the original coding tree
    writeLabel(rTree, label, &pos, 1);
    printPre(rTree);
    long strLen = 0; // length of the decoded string
    char* dString = decoded(fp, rTree, &strLen, totalByte, treeByte, stringByte, &rByte, &rBit); // get decoded string, file closes here
    if(strLen != stringByte){
        fprintf(stderr, "Unable to decode the original string.");
        return EXIT_FAILURE;
    }
    if(writeOutput2(argv[3], dString, strLen) == false){
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
    Node* head = makeSortedLL(characters); // linked list for building huffman tree
    TreeNode* hTree = buildHuffTree(head); // the huffman tree to be encoded
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
