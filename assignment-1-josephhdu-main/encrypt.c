/*
* This program encrypts and decrypt messages based on command line input
* Usage: ./encrypt -t <mappingfile> -m <encryption mode> -i <inputfile>
* Author: Joseph Du
* Collaborators: N/A

Joseph Du, 1725433, jdu8, B1, Henry Tang, LAB H02

CMPUT 201 Student Submission License Version 2.0

Copyright 2023 <student name>

Unauthorized redistribution is forbidden under all circumstances. Use of this software without explicit authorization from the author and the CMPUT 201 Instructor is prohibited.

This software was produced as a solution for an assignment or lab in the course CMPUT 201 - Practical Programming Methodology at the University of Alberta, Canada. This solution is confidential and remains confidential after it is submitted for grading. The course staff has the right to run plagiarism-detection tools on any code developed under this license, even beyond the duration of the course.

Copying any part of this solution without including this copyright notice is illegal.

If any portion of this software is included in a solution submitted for grading at an educational institution, the submitter will be subject to the plagiarism sanctions at that institution.

This software cannot be publicly posted under any circumstances, whether by the original student or by a third party. If this software is found in any public website or public repository, the person finding it is kindly requested to immediately report, including the URL or other repository locating information, to the following email addresses:

      hktang@ualberta.ca

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 30

// Function declarations
void encrypt(char *mappingfile, char *inputfile);
void decrypt(char *mappingfile, char *inputfile);

/*
* Main Function
* Paramerters:
* argc - number of command line argument
* argv - pointer array to each command line input
*/
int main(int argc, char *argv[]){

    if(argc != 7){ //checks for the correct number of command line arguments passed
        fprintf(stderr, "Usage: ./encrypt -t <mappingfile> -m <encryption mode> -i <inputfile>\n");
        exit(7);//change exit
    }


    char *mappingfile, *encryption_mode, *inputfile;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0) {
            mappingfile = argv[i + 1];
            i++;

            FILE *mapfile = fopen(argv[i], "r");
            if(mapfile == NULL){
                fprintf(stderr, "Error: Mapping file <Name of mapping file> does not exist\n");
                exit(3);
            }
            fclose(mapfile);

        } else if (strcmp(argv[i], "-m") == 0) {
            encryption_mode = argv[i + 1];
            i++;

            int valid_mode = 0;

            if(strcmp(encryption_mode, "1") == 0 || strcmp(encryption_mode, "2") == 0){
                valid_mode = 1;
            }

            if(valid_mode != 1){
                fprintf(stderr, "You entered <value of incorrect mode>. Sorry, your mode must be 1 for encryption or 2 for decryption\n");
                exit(6);
            }

        } else if (strcmp(argv[i], "-i") == 0) {
            inputfile = argv[i + 1];
            i++;

            FILE *infile = fopen(argv[i], "r");
            if(infile == NULL){
                fprintf(stderr, "Error: Input word file <Name of input file> does not exist\n");
                exit(5);
            }
            fclose(infile);
        }
    }


    //format of the mappingfile is correct
    FILE *mapfile = fopen(mappingfile, "r");
    int lines = 0;
    char line[MAX_STRING];
    int flag = 0;

    while (fgets(line, MAX_STRING, mapfile) != NULL){
        if((int)line[0] < 97 || (int)line[0] > 122){
            flag = 1;
        } else if((int)line[1] != 44){
            flag = 1;
        } else if((int)line[2] < 97 || (int)line[2] > 122){
            flag = 1;
        }
        
        lines++;
    }

    if(lines != 26){
        flag = 1;
    }

    if(flag == 1){
        fprintf(stderr, "Error: The format of mapping file <Name of mapping file> is incorrect\n");
        exit(4);
    }

    char mode = encryption_mode[0];

    if(mode == '1'){
        encrypt(mappingfile, inputfile);
    } else if(mode == '2'){
        decrypt(mappingfile, inputfile);
    }

    return 0;

}

/*
* Encryption function
* - encrypts the text file and prints out encryption
* Parameters:
* mappingfile - the mapping file name
* inputfile - the input file name
*/
void encrypt(char *mappingfile, char *inputfile){
    // handles inputfiles
    FILE *infile = fopen(inputfile, "r");
    int inputfile_line_number = 1;
    char file_line[MAX_STRING];

    // handles mapping file
    FILE *mapfile = fopen(mappingfile, "r");

    char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    char alphabet_mapping[26];

    char mapping_line[4];

    int alphabet_mapping_init_index = 0;

    while(fgets(mapping_line, MAX_STRING, mapfile) != NULL){
        alphabet_mapping[alphabet_mapping_init_index] = mapping_line[2];
        alphabet_mapping_init_index++;
    }

    while (fgets(file_line, MAX_STRING, infile) != NULL) {

        int word_length = strlen(file_line);

        if(file_line[word_length - 1] == '\n'){
            word_length--;
            file_line[word_length] = '\0';
        }

        char encrypted_word[word_length];

        if(inputfile_line_number == 1){
            int fix_line_one_len = strlen(file_line);
            for(int i = 0; i < fix_line_one_len; i++){
                for(int j = 0; j < 26; j++){
                    if(file_line[i] == alphabet[j]){
                        encrypted_word[i] = alphabet_mapping[j];
                    }
                }
            }
            
            for(int i = word_length - 1; i >= 0; i--){
                fprintf(stdout,"%c",encrypted_word[i]);
            }
            
            fprintf(stdout,"\n");

        } else{
            for(int i = 0; i < word_length; i++){
                for(int j = 0; j < 26; j++){
                    if(file_line[i] == alphabet[j]){
                        encrypted_word[i] = alphabet_mapping[j];
                    }
                }
            }

            char reversed_word[word_length];
            for(int i = 0; i < word_length; i++){
                reversed_word[i] = encrypted_word[word_length - i - 1];
            }
            reversed_word[word_length] = '\0';
            fprintf(stdout,"%s\n", reversed_word);
        }
        inputfile_line_number++;
    }
    fclose(infile);
}

/*
* Decryption function
* - decrypts the text file and prints out decryption
* Parameters:
* mappingfile - the mapping file name
* inputfile - the input file name
*/
void decrypt(char *mappingfile, char *inputfile){
    // handles inputfiles
    FILE *infile = fopen(inputfile, "r");
    int inputfile_line_number = 1;
    char file_line[MAX_STRING];

    // handles mapping file
    FILE *mapfile = fopen(mappingfile, "r");

    char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    char alphabet_mapping[26];

    char mapping_line[4];

    int alphabet_mapping_init_index = 0;

    while(fgets(mapping_line, MAX_STRING, mapfile) != NULL){
        alphabet_mapping[alphabet_mapping_init_index] = mapping_line[2];
        alphabet_mapping_init_index++;
    }

    while (fgets(file_line, MAX_STRING, infile) != NULL) {

        int word_length = strlen(file_line);

        if(file_line[word_length - 1] == '\n'){
            word_length--;
            file_line[word_length] = '\0';
        }

        char encrypted_word[word_length];


        if(inputfile_line_number == 1){
            int fix_line_one_len = strlen(file_line);
            for(int i = 0; i < fix_line_one_len; i++){
                for(int j = 0; j < 26; j++){
                    if(file_line[i] == alphabet[j]){
                        encrypted_word[i] = alphabet_mapping[j];
                    }
                }
            }
            
            for(int i = word_length - 1; i >= 0; i--){
                fprintf(stdout,"%c",encrypted_word[i]);
            }
            
            fprintf(stdout,"\n");

        } else{
            for(int i = 0; i < word_length; i++){
                for(int j = 0; j < 26; j++){
                    if(file_line[i] == alphabet[j]){
                        encrypted_word[i] = alphabet_mapping[j];
                    }
                }
            }

            char reversed_word[word_length];
            for(int i = 0; i < word_length; i++){
                reversed_word[i] = encrypted_word[word_length - i - 1];
            }
            reversed_word[word_length] = '\0';
            fprintf(stdout,"%s\n", reversed_word);
        }
        inputfile_line_number++;
    }
    fclose(infile);
}