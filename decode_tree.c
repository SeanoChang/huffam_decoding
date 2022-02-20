#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Struct.h"
#include "decode_tree.h"

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
    while(fread(&oneByte, sizeof(char), 1, fp) != 0 && readCount < *treeByte){
        for(int i = 0; i < 8;i++){
            bitPatterns[i + readCount*8] = oneByte & 1;
            oneByte = oneByte >> 1;
        }    
        readCount++;
    }
	
    return bitPatterns;
}

char readBitToChar(char* pattern){
    char bp[9] = {'\0'};

    for(int i = 7; i >= 0; i--){
    	bp[7-i] = pattern[i];
    }

    int rtv = strtol(bp, 0, 2); // return value is the char readed from the bit pattern

    return (char)rtv;
}

long decoded(FILE* fp, TreeNode* tn, char* ds, long totalByte, long treeByte, long stringByte, long* byte, int* bit){
    if(fp == NULL){
        fprintf(stderr, "File pointer does not have a reference.");
        return 0;
    }

    long toGet = totalByte - treeByte - 3*sizeof(long);

    int* ptn = malloc(sizeof(int) * toGet*8); // the pattern to be decoded

    char oneByte;
    long readCount = 0;
    fseek(fp, -1, SEEK_CUR);
    while(fread(&oneByte, sizeof(char), 1, fp) != 0 && readCount <= toGet){
        for(int i = 0; i < 8;i++){
            ptn[i + readCount*8] = oneByte & 1;
            oneByte = oneByte >> 1;
        }    
        readCount++;
    }
    printf("\n");
    for(int i = 0; i < toGet*8; i++){
        printf("%d", ptn[i]);
    }
    printf("\n");

    readCount = 0;
    long pos = 0;
    int i = 0;
    ds[0] = '\0';
    while(readCount < stringByte){
        int len = strlen(ds);
        if(len < readCount+1){
            char* temp = realloc(ds, sizeof(char)*len*2);
            if(temp != NULL){
                ds = temp;
            }
        }
        ds[i] = getChar(tn, ptn, &pos); // ds stands for decoded string.
        printf("this is %c\n", ds[i]);
        if(ds[i] == '\0'){
            return 0;
        }
        readCount++;
    }

    *byte = pos / 8;
    *bit = pos % 8;
	
	fclose(fp);
    return readCount;
}

char getChar(TreeNode* root, int* ptn, long* pos){
    if(root -> leaf == 1){
        printf("im here %c and ", root -> value);
        return root->value;
    }

    char c = '\0';
    if(ptn[*pos] == 0){
	    *pos+=1;
        c = getChar(root->left, ptn, pos);
    } else if(ptn[*pos] == 1){
	    *pos+=1;
        c = getChar(root->right, ptn, pos);
    } else{
        fprintf(stderr, "Cannot determine whether the tree node is a leaf or not.");
        return c;
    }

    return c;
}
