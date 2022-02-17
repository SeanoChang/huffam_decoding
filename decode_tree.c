#include <stdio.h>
#include <stdlib.h>

#include "huffman_tree.h"

int* readBitPattern(FILE* fp, long* totalByte, long* treeByte, long* stringByte){
    if(fread(totalByte, sizeof(long), 1, fp) == 0){
        fprintf(stderr, "Cannot read the total byte.");
        fclose(fp);
        return NULL;
    }
    if(fread(treeByte, sizeof(long), 1, fp) == 0){
        fprintf(stderr, "Cannot read the coding tree byte.");
        fclose(fp);
        return NULL;
    }
    if(fread(stringByte, sizeof(long), 1, fp) == 0){
        fprintf(stderr, "Cannot read the original string byte.");
        fclose(fp);
        return NULL;
    }

    int* bitPatterns = malloc(sizeof(int) * *treeByte * 8);

    char oneByte;
    long readCount = 0;
    while(fread(&oneByte, sizeof(char), 1, fp) != 0 && readCount <= *treeByte){
        for(int i = 0; i < 8;i++){
            bitPatterns[i + readCount*8] = oneByte & 1;
            oneByte = oneByte >> 1;
        }    
        readCount++;
    }

    return bitPatterns;
}

char readBitToChar(int* pattern){
    char* bp[8] = '\0' * 8;

    for(int i = 7; i >= 0; i--){
        if(pattern[i] == 1){
            bp[7-i] = '1';
        }
        else{
            bp[7-i] = '0';
        }
    }

    char rtv = strtol(bp, 0, 2); // return value is the char readed from the bit pattern

    return rtv;
}

long decoded(FILE* fp, TreeNode* tn, char* ds, long* totalByte, long* treeByte, long* stringByte){
    if(fp == NULL){
        fprintf(stderr, "File pointer does not have a reference.");
        return 0;
    }

    long toGet = *totalByte - *treeByte - 3*sizeof(long);

    int* ptn = malloc(sizeof(int) * toGet*8); // the pattern to be decoded

    char oneByte;
    long readCount = 0;
    while(fread(&oneByte, sizeof(char), 1, fp) != 0 && readCount <= toGet){
        for(int i = 0; i < 8;i++){
            ptn[i + readCount*8] = oneByte & 1;
            oneByte = oneByte >> 1;
        }    
        readCount++;
    }

    readCount = 0;
    int pos = 0;
    int i = 0;
    while(readCount < *stringByte){
        ds[i] = getChar(tn, ptn, &pos); // ds stands for decoded string.
        if(ds[i] == '\0'){
            return 0;
        }
        readCount++;
    }

    return readCount;
}

char getChar(TreeNode* root, int* ptn, long* pos){
    if(root -> leaf == 1){
        return root->value;
    }

    char c = '\0';
    *pos+=1;
    if(ptn[*pos] == 0){
        c = getChar(root->left, ptn, *pos);
    } else if(ptn[*pos] == 1){
        c = getChar(root->right, ptn, *pos);
    } else{
        fprintf(stderr, "Cannot determine whether the tree node is a leaf or not.");
        return c;
    }

    return c;
}
