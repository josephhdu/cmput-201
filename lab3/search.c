#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *words;
    int freq[26] = {0};// to store the frequency of letters a = 0 ...

    if (argc != 3){ //checks for the correct number of command line arguments passed
        fprintf(stderr, "Usage: ./search <input file> <threshold>\n");
        exit(EXIT_FAILURE);
    }
    int threshold = atoi(argv[2]);

    if ((words = fopen(argv[1], "r")) == NULL){ //checks if input file exists
        fprintf(stderr, "Error: cannot find %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    char word[11] = {0}; //initialized to 11 because word will have at most 10 letters and 1 extra is needed for '\0'
    while (fscanf(words, " %s", word) == 1){
        for(int i = 0; i < 10; i++){
            char temp = word[i];

            if(temp == '\0'){
                break;
            }
            
            int letter = ((int) temp) - 97;
            freq[letter]++;
        }
    }
    
    int flag = 0;
    char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    
    for(int i = 0; i < 26; i++){
        
        if(freq[i] > threshold){
            if(freq[i] == 1){
                printf("%c appears %d time\n", alphabet[i],freq[i]);
            } else{
                printf("%c appears %d times\n", alphabet[i],freq[i]);
            }
            flag = 1;
        }
    }
    
    if(flag == 0){
        printf("There are no letters that exceed this threshold\n");
    }

    fclose(words);
}