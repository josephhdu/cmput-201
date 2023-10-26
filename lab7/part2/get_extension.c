#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 20

int get_extension(const char *file_name);

int main(int argc, char* argv[]){
	
	//simplifying things and not doing any argument validation
    printf("The index value of the extension of the input file is: %d\n", get_extension(argv[1]));
}

int get_extension(const char *file_name){

    static char *extentions[] = {".txt", ".out", ".bkp", ".dot", ".tx"};

    const char *extention;
    int len;
    len = strlen(file_name);
    int i;

    for(i = len - 1; i >= 0; i--){ //points extention to the last . in filename
        if(file_name[i] == '.'){
            extention = file_name + i;
            break;
        }
    }

    if(!extention){
        return -1;
    }

    for(i = 0; i < 5; i++){
        if(strcmp(extention, extentions[i]) == 0){
            return i;
        }
    }
    return -1;
}