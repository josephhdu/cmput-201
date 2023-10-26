#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "puzzle2D.h"
#define P 7079
#define D 256

int main(int argc, char *argv[]){

    char *puzzleFile, *wordLen, *wordlistFile, *solutionFile;

// error handling 
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0){
            puzzleFile = argv[i + 1];
            
            FILE *pf = fopen(puzzleFile, "r");
            if(pf == NULL){
                fprintf(stderr, "Error: Puzzle file %s does not exist\n", argv[i + 1]);    
                exit(4);
            }
            fclose(pf);

        } else if (strcmp(argv[i], "-l") == 0){
            wordLen = argv[i + 1];

            if(wordLen == NULL){
                fprintf(stderr, "Usage: ./wordSearch2D -p <puzzle_file> -l <word_length> -w <wordlist_file> [-o <solution_file>]\n");
                exit(6);
            }

        } else if (strcmp(argv[i], "-w") == 0){
            wordlistFile = argv[i + 1];

            FILE *wlf = fopen(wordlistFile, "r");
            if(wlf == NULL){
                fprintf(stderr, "Error: Wordlist file %s does not exist\n", argv[i + 1]);
                exit(5);
            }
            fclose(wlf);

        } else if (strcmp(argv[i], "-o") == 0){
            solutionFile = argv[i + 1];
        }
    }

    if(puzzleFile == NULL || wordLen == NULL || wordlistFile == NULL){
        fprintf(stderr, "Usage: ./wordSearch2D -p <puzzle_file> -l <word_length> -w <wordlist_file> -o <solution_file>]\n");
        exit(6);
    }

// This is to change the word length to a integer value
    int wordLength;
    wordLength = atoi(wordLen);

// This is to create a 2D array to store the puzzle grid
    FILE *puzfile = fopen(puzzleFile, "r");
    char line[100];
    int n = (sizeof(fgets(line, 100, puzfile))- 2); //minus 2 b/c \0 and \n **********
    char grid[n][n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(puzfile, " %c", &grid[i][j]);
        }
    }

    fclose(puzfile);

// This is to create an array of strings to store the words
    FILE *wordfile = fopen(wordlistFile, "r");
    int wordfilelines = 0;
    char wordline[100];
    while(fgets(wordline, 100, wordfile) != NULL){
        wordfilelines++;
    }


    fclose(wordfile);

//need to open the file again the first time already iterated to the end
    FILE *wordfile2 = fopen(wordlistFile, "r");
    char words[wordfilelines][wordLength + 2];

    for(int i = 0; i < wordfilelines && fscanf(wordfile2, "%s", words[i]) != -1; i++) {
    }

    fclose(wordfile2);


//opens solution file
    FILE *solFile = fopen(solutionFile, "w");

//changes target words to be in hash for for easier use later

    int hashWords[wordfilelines];
    for(int i = 0; i < wordfilelines; i++){
        hashWords[i] = hash(words[i]);
    }


// Horizontal right initialization
    char *horRight[n];
    for(int i = 0; i < n; i++){
        horRight[i] = malloc(n + 1);

        for(int j = 0; j < n; j++) {
            horRight[i][j] = grid[i][j];
        }
        horRight[i][n] = '\0';
        //printf("%s\n", horRight[i]);
    }

//Horizontal left initialization
    char *horLeft[n];
    for(int i = 0; i < n; i++){
        horLeft[i] = malloc(n + 1);
        horLeft[i] = reverse2(horRight[i]);
    }

//Vertical down initialization
    char *vertDown[n];
    for(int i = 0; i < n; i++){
        vertDown[i] = malloc(n + 1);

        for(int j = 0; j < n; j++) {
            vertDown[i][j] = grid[j][i];
        }
        vertDown[i][n] = '\0';
    }

//Vertical up initialization
    char *vertUp[n];
    for(int i = 0; i < n; i++){
        vertUp[i] = malloc(n + 1);
        vertUp[i] = reverse2(vertDown[i]);
    }

//Diagonal (mode 5) initialization

    int diagN = 2 * n - 1;

    char *diag5[diagN];
    for (int i = 0; i < diagN; i++) {
        diag5[i] = malloc(n + 1);  // add 1 for the null terminator
        
        int startRow, startCol;
        if (i < n) {
          startRow = 0;
          startCol = n - i - 1;
        } else {
          startRow = i - n + 1;
          startCol = 0;
        }
        for (int j = 0; j < n && startRow < n && startCol < n; j++, startRow++, startCol++) {
            diag5[i][j] = grid[startRow][startCol];
        }
        diag5[i][n] = '\0'; 
    }

//Diagonal (mode 6) initialization

    char *diag6[diagN];
    for(int i = 0; i < diagN; i++){
        diag6[i] = malloc(n + 1);
        diag6[i] = reverse2(diag5[i]);
    }

//Diagonal (mode 8) initialization

    char *diag8[diagN];
    for(int i = 0; i < diagN; i++) {// calculate the start and end indices for the diagonal
        int startRow, startCol, endRow, endCol;
        if (i < n) {
            startRow = 0;
            startCol = i;
            endRow = i;
            endCol = 0;
        } else {
            startRow = i - n + 1;
            startCol = n - 1;
            endRow = n - 1;
            endCol = i - n + 1;
        }
    
        int diagLen = endRow - startRow + 1;
        diag8[i] = malloc(diagLen + 1);

        int k = 0;
        for (int row = startRow, col = startCol; row <= endRow && col >= endCol; row++, col--) {
            diag8[i][k++] = grid[row][col];
        }
        diag8[i][k] = '\0'; 
    }

//Diagonal (mode 7) initialization

    char *diag7[diagN];
    for(int i = 0; i < diagN; i++){
        diag7[i] = malloc(n + 1);
        diag7[i] = reverse2(diag8[i]);
    }

    for(int k = 0; k < wordfilelines; k++){

        int flag = 0;

//Horizontal right checking

        for(int i = 0; i < n; i++){

            int matchIndex = rollingHash(horRight[i], wordLength, hashWords[k]);
            //printf("match index is %d\n", matchIndex);

            if(matchIndex != -1){ // so if a match is found
                fprintf(solFile, "%s;(%d,%d);1\n", words[k], i, matchIndex);
                flag = 1;
            }
        }  

//Horizontal Left checking

        for(int i = 0; i < n; i++){

            int matchIndex = rollingHash(horLeft[i], wordLength, hashWords[k]);

            if(matchIndex != -1){ // so if a match is found
                fprintf(solFile, "%s;(%d,%d);2\n", words[k], i, matchIndex + wordLength - 1);
                flag = 1;
            }
        }

//Vertical down checking

        for(int i = 0; i < n; i++){
            int matchIndex = rollingHash(vertDown[i], wordLength, hashWords[k]);

            if(matchIndex != -1){ // so if a match is found
                fprintf(solFile, "%s;(%d,%d);3\n", words[k], matchIndex, i);
                flag = 1;
            }
        }
        
//Vertical up checking

        for(int i = 0; i < n; i++){
            int matchIndex = rollingHash(vertUp[i], wordLength, hashWords[k]);

            if(matchIndex != -1){ // so if a match is found
                fprintf(solFile, "%s;(%d,%d);4\n", words[k], wordLength - matchIndex + 1, i);
                flag = 1;
            }
        }

//Diagonal (mode 5) checking

        for(int i = 0; i < diagN; i++){
            int matchIndex = rollingHash(diag5[i], wordLength, hashWords[k]);

            if(matchIndex != -1){ // so if a match is found
            //need to at 1 to i because it it too low
                if(i + 1 == n){
                    fprintf(solFile, "%s;(%d,%d);5\n", words[k], matchIndex, matchIndex);
                    flag = 1;
                } else if(i + 1 < n){
                    int x = n - i + matchIndex + 1;
                    fprintf(solFile, "%s;(%d,%d);5\n", words[k], matchIndex, x);
                    flag = 1;
                } else if(i + 1 > n){
                    int y = i + 1 - n + matchIndex;
                    fprintf(solFile, "%s;(%d,%d);5\n", words[k], y, matchIndex);
                    flag = 1;
                }
            }
        }

//Diagonal (mode 6) checking


        for(int i = 0; i < diagN; i++){
            int matchIndex = rollingHash(diag6[i], wordLength, hashWords[k]);


            if(matchIndex != -1){
                if(i + 1 == n){
                    fprintf(solFile, "%s;(%d,%d);6\n", words[k], n - 1 - matchIndex, n - 1 - matchIndex);
                    flag = 1;
                } else if(i + 1 < n){
                    int y = i - matchIndex;// maybe remove +1
                    int x = n - matchIndex - 1;//maybe -1
                    fprintf(solFile, "%s;(%d,%d);6\n", words[k], y, x);
                    flag = 1;
                } else if(i + 1 > n){
                    int y = n - matchIndex - 1;
                    int x = n - (i + 1 - n + matchIndex) - 1;
                    fprintf(solFile, "%s;(%d,%d);6\n", words[k], y, x);
                    flag = 1;
                }
            }
        }


//Diagonal (mode 7) checking

        for(int i = 0; i < diagN; i++){
            int matchIndex = rollingHash(diag7[i], wordLength, hashWords[k]);

            if(matchIndex != -1){
                if(i + 1 == n){
                    int y = i - matchIndex;
                    int x = matchIndex;
                    fprintf(solFile, "%s;(%d,%d);7\n", words[k], y, x);
                    flag = 1;
                } else if(i + 1 < n){
                    int y = i - matchIndex;
                    int x = matchIndex;
                    fprintf(solFile, "%s;(%d,%d);7\n", words[k], y, x);
                    flag = 1;
                } else if(i + 1 > n){
                    int y = n - matchIndex - 1;
                    int x = matchIndex + (i + 1 - n);
                    fprintf(solFile, "%s;(%d,%d);7\n", words[k], y, x);
                    flag = 1;
                }
            }
        }


//Diagonal (mode 8) checking

        for(int i = 0; i < diagN; i++){
            int matchIndex = rollingHash(diag8[i], wordLength, hashWords[k]);

            if(matchIndex != -1){
                if(i + 1 == n){
                    int y = matchIndex;
                    int x = n - matchIndex - 1;
                    fprintf(solFile, "%s;(%d,%d);8\n", words[k], y, x);
                    flag = 1;
                } else if(i + 1 < n){
                    int y = matchIndex;
                    int x = i + 1 - matchIndex;
                    fprintf(solFile, "%s;(%d,%d);8\n", words[k], y, x);
                    flag = 1;
                } else if(i + 1 > n){
                    int y = (matchIndex) + (i + 1 - n);
                    int x = n - matchIndex - 1;
                    fprintf(solFile, "%s;(%d,%d);8\n", words[k], y, x);
                    flag = 1;
                }
            }
        }

        if(flag == 0){ // word then is not found
            fprintf(solFile, "%s;(0,0);0\n", words[k]);
        }

    }

}
