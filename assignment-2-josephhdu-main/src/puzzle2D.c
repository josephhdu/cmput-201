#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "puzzle2D.h"
#define P 7079
#define D 256

int hash(char hashStr[]){
    int previousHash = 0;
    int strSize = strlen(hashStr);

    for(int i = 0; i < strSize; i++){
        previousHash = (D * previousHash + hashStr[i]) % P;
    }

    return previousHash;
}

int rollingHash(char str[], int n, int targetHash){ //** need to fix rolling hash to return mutiple potential matches in the string
    
    int rehashCoef = (int)pow(D, n - 1) % P;
    int strSize = strlen(str);
    int currentHash = 0;

    for (int i = 0; i < strSize; i++) {
        
        if(i < n){
            currentHash = (D * currentHash + str[i]) % P;           
        }

        if(i >= n){
            currentHash = (D * (currentHash - str[i - n] * rehashCoef) + str[i]) % P;
            if(currentHash < 0){
                currentHash = P + currentHash;
            }
        }

        if(currentHash == targetHash){
            return(i - n + 1);
        }
    }
    return -1; // if no match is found
}

void reverse(char *str) {
    int length = strlen(str);
    char temp;

    for (int i = 0; i < length / 2; i++) {
        temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
}

char* reverse2(const char *str) {
    int length = strlen(str);
    char* reversed = (char*) malloc(length + 1);

    for (int i = 0; i < length; i++) {
        reversed[i] = str[length - i - 1];
    }

    reversed[length] = '\0';

    return reversed;
}
