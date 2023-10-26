#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_randomwalk(int n, int m, char walk[n][m]);
void print_array (int rows, int cols, char grid[rows][cols]);

int main(){
    int rows, cols;
    printf("Enter number of rows: ");
    scanf(" %d", &rows);
    printf("Enter number of columns: ");
    scanf(" %d", &cols);

    char grid[rows][cols];

    generate_randomwalk(rows, cols, grid);
    print_array(rows, cols, grid);
    }

//hell0
void print_array (int rows, int cols, char grid[rows][cols]){
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
}

void generate_randomwalk(int rows, int cols, char grid[rows][cols]){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = '.';
        }
    }

    char alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};// maybe don't initialize it as a string because then it adds a newline automatically
    int alphabetIndex = 0;

    int rowIndex = 0;
    int colIndex = 0;

    grid[rowIndex][colIndex] = alphabet[alphabetIndex];
    ++alphabetIndex;

    srand(time(NULL));

    while(1){
        int roll = (rand() % 4);

//termination
        if(alphabetIndex >= 26){
            printf("Walked until letter %c\n", alphabet[alphabetIndex - 1]);
            break;
        } else if(rowIndex == 0 && colIndex == 0 && grid[rowIndex + 1][colIndex] != '.' && grid[rowIndex][colIndex + 1] != '.'){ //top left
            printf("Walked until letter %c\n", alphabet[alphabetIndex - 1]);
            break;
        } else if(rowIndex == 0 && colIndex == cols - 1 && grid[rowIndex + 1][colIndex] != '.' && grid[rowIndex][colIndex - 1] != '.'){ //top right
            printf("Walked until letter %c\n", alphabet[alphabetIndex - 1]);
            break;
        } else if(rowIndex == rows - 1 && colIndex == cols - 1 && grid[rowIndex - 1][colIndex] != '.' && grid[rowIndex][colIndex - 1] != '.'){ // bottom right
            printf("Walked until letter %c\n", alphabet[alphabetIndex - 1]);
            break;
        } else if(rowIndex == rows - 1 && colIndex == 0 && grid[rowIndex - 1][colIndex] != '.' && grid[rowIndex][colIndex + 1] != '.'){ // bottom left
            printf("Walked until letter %c\n", alphabet[alphabetIndex - 1]);
            break;
        } else if(grid[rowIndex - 1][colIndex] != '.' && grid[rowIndex][colIndex + 1] != '.' && grid[rowIndex + 1][colIndex] != '.' && grid[rowIndex][colIndex - 1] != '.'){ // middle
            printf("Walked until letter %c\n", alphabet[alphabetIndex - 1]);
            break;
        }


        if(roll == 0){ //move up
            if(rowIndex != 0){
                if(grid[rowIndex - 1][colIndex] == '.'){
                    rowIndex--;
                    grid[rowIndex][colIndex] = alphabet[alphabetIndex];
                    alphabetIndex++;
                }
            }

        } else if(roll == 1){ //move right
            if(colIndex != cols - 1){
                if(grid[rowIndex][colIndex + 1] == '.'){
                    colIndex++;
                    grid[rowIndex][colIndex] = alphabet[alphabetIndex];
                    alphabetIndex++;
                }
            }

        } else if(roll == 2){ //move down
            if(rowIndex != rows - 1){
                if(grid[rowIndex + 1][colIndex] == '.'){
                    rowIndex++;
                    grid[rowIndex][colIndex] = alphabet[alphabetIndex];
                    alphabetIndex++;
                }
            }

        } else if(roll == 3){ // move left
            if(colIndex != 0){
                if(grid[rowIndex][colIndex - 1] == '.'){
                    colIndex--;
                    grid[rowIndex][colIndex] = alphabet[alphabetIndex];
                    alphabetIndex++;
                }
            }
        }
    }
}