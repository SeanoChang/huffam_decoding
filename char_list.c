#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "char_list.h"

long* countChar(char* dString){
    long* count = malloc(sizeof(long) * 256);

    for(int i = 0; i < 256; i++){
        count[i] = 0;
    }

    long len = strlen(dString);

    for(int i = 0; i < len; i++){
        int c = (int)(dString[i]);
        count[c]++;
    }

    return count;
}

