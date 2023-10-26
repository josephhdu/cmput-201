#include <stdio.h>
#include <stdlib.h>

int main(){
    char** words = malloc(20 * sizeof(char*));
    int n = 0;

    while(n < 5) {
        printf("Enter word: ");
        char* word = malloc(21 * sizeof(char));
        scanf("%s", word);
        if (*word == NULL) {
            free(word);
            break;
        }
        words[n] = word;
        n++;
    }

    if (n == 0) {
        printf("Enter word:\nNo words inserted.\n");
        return 0;
    }

    printf("In sorted order:");
    for (int i = 0; i < n; i++) {
        printf(" %s", words[i]);
        free(words[i]);
    }
    printf(".\n");

    free(words);
    return 0;
}