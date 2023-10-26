#include <stdio.h>
#include <stdlib.h>


int main(){
    char message[100];
    char *p = &message[0];
    char character;

    printf("Enter a message: ");

    int n = 0;

    while((character = getchar()) != '\n'){
        n++;
        *(p++) = character;
    }

    if((n % 2) == 1){ // in case the n is odd
        n = n/2;
        p = p - n - 2;
    } else{ // in case n is even
        n = n/2;
        p = p - n - 1;
    }

    printf("Reversal of the first half: ");

    for(int i = 0; i < n; i++){
        putchar(*p--);
    }

    printf("\n");

    return 0;
}