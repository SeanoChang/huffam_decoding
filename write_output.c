#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "write_output.h"

void writePreOrder(FILE*, TreeNode*);

bool writeOutput1(char* outfile1, TreeNode* tn){ // tn stands for treenode
    FILE * fp = fopen(outfile1, "wb");
    if(fp == NULL){
        fprintf(stderr, "Cannot open output file 1.");
        return false;
    }

    writePreOrder(fp, tn);
    fclose(fp);
    return true;
}

bool writeOutput2(char* outfile2, char* ds){ // ds stands for decoded string
    FILE * fp = fopen(outfile2, "wb");
    if(fp == NULL){
        fprintf(stderr, "Cannot open output file 2.");
        return false;
    }
}

bool writeOutput3(char* outfile3, long* count){
    FILE * fp = fopen(outfile3, "wb");
    if(fp == NULL){
        fprintf(stderr, "Cannot open output file 3.");
        return false;
    }

    if(fwrite(count, sizeof(long), 256, fp) == 0){
        fprintf(stderr, "Cannot write output to output file 3.");
        fclose(fp);
        return false;
    }

    return true;
}

bool writeOutput4(char* outfile4, TreeNode* tn){
    FILE * fp = fopen(outfile4, "wb");
    if(fp == NULL){
        fprintf(stderr, "Cannot open output file 4.");
        return false;
    }
}

bool writeOutput5(char*outfile5, TreeNode* tn){
    FILE * fp = fopen(outfile5, "wb");
    if(fp == NULL){
        fprintf(stderr, "Cannot open output file 5.");
        return false;
    }
}

void writePreOrder(FILE* fp, TreeNode* tn){
    if(tn == NULL){
        return;
    }

    fwrite(&tn->leaf, sizeof(char), 1, fp);
    if(tn->leaf == '1'){
        fwrite(&tn->value, sizeof(char), 1, fp);
    }
    writePreOrder(fp, tn->left);
    writePreOrder(fp, tn->right);
}
