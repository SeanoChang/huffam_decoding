#include <stdio.h>
#include <stdlib.h>

#include "char_list.h"
#include "huffman_tree.h"
#include "decode_tree.h"

int* readBitPattern(char* inputFile, long* totalByte, long* treeByte, long* stringByte){
    FILE* fp = fopen(inputFile, "rb");
    if(fp == NULL){
        fclose(fp);
        fprintf(stderr, "Cannot open input file for reading!");
        return NULL;
    }

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

    for(int i = 0; i < *treeByte*8; i++){
        fprintf(stdout, "%d ", bitPatterns[i]);
    }

    fclose(fp);
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
