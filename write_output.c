#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Struct.h"
#include "write_output.h"

void writePreOrder(FILE*, TreeNode*);

bool writeOutput1(char* outfile1, TreeNode* tn){ // tn stands for treenode
    FILE * fp = fopen(outfile1, "wb");
    if(fp == NULL){
        fprintf(stderr, "Cannot open output file 1.\n");
        return false;
    }

    writePreOrder(fp, tn);

    fclose(fp);
    return true;
}

bool writeOutput2(char* outfile2, char* ds, long strLen){ // ds stands for decoded string
    FILE * fp = fopen(outfile2, "wb");
    if(fp == NULL){
        fprintf(stderr, "Cannot open output file 2.\n");
        return false;
    }

    for(int i = 0; i < strLen; i++){
        if(fwrite(&ds[i], sizeof(char), 1, fp) != 1){
            fprintf(stderr, "Cannot write into file.\n");
            return false;
        }
    }

	fclose(fp);
    return true;
}

bool writeOutput3(char* outfile3, long* count){
    FILE * fp = fopen(outfile3, "wb");
    if(fp == NULL){
        fprintf(stderr, "Cannot open output file 3.\n");
        return false;
    }

    if(fwrite(count, sizeof(long), 256, fp) == 0){
        fprintf(stderr, "Cannot write output to output file 3.\n");
        fclose(fp);
        return false;
    }
	fclose(fp);
    return true;
}

bool writeOutput4(char* outfile4, TreeNode* tn){
    FILE * fp = fopen(outfile4, "wb");
    if(fp == NULL){
        fprintf(stderr, "Cannot open output file 4.\n");
        return false;
    }

    writePreOrder(fp, tn);
    fclose(fp);
    return true;
}

bool writeOutput5(char*outfile5, long rByte, int rBit, long hTreeBit){
    FILE * fp = fopen(outfile5, "wb");
    if(fp == NULL){
        fprintf(stderr, "Cannot open output file 5.\n");
        return false;
    }
    long hByte = hTreeBit / 8;
    int hBit = hTreeBit % 8;

    fwrite(&rByte, sizeof(long), 1, fp);
    fwrite(&rBit, sizeof(int), 1, fp);
    fwrite(&hByte, sizeof(long), 1, fp);
    fwrite(&hBit, sizeof(int), 1, fp);
 	fclose(fp);   
    return true;
}

void writePreOrder(FILE* fp, TreeNode* tn){
    if(tn == NULL){
        return;
    }

    if(tn->leaf == 0) {
        char c = '0';
        if(fwrite(&c, sizeof(char), 1, fp) != 1) {
            fprintf(stderr, "Unable to write to output file.\n");
        }
    } else if(tn->leaf == 1) {
        char c = '1';
        if(fwrite(&c, sizeof(char), 1, fp) != 1){ 
            fprintf(stderr, "Unable to write to output file.\n");
        }
    }
    if(tn->leaf == 1){
        if(fwrite(&tn->value, sizeof(char), 1, fp) != 1) {
            fprintf(stderr, "The tree is not properly constructed. (no value)\n");
            return;
        }
    }

    writePreOrder(fp, tn->left);
    writePreOrder(fp, tn->right);
}

