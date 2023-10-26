#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int check_palindrome(char *message);

int main(){
    printf("Enter a message: ");
    
    char message[100];
    fgets(message, 100, stdin);

    if(check_palindrome(message) == 1){
        printf("Not a palindrome\n");
    } else{
        printf("Palandrome\n");
    }
}

int check_palindrome(char *message){
    

    int i = 0;
    char *p;
    p = &message[0];
    while(*p != '\0'){
        *p = tolower(*p);
        p++;
    }



    char *beginning, *end;
    beginning = &message[0];
    end = &message[i - 1];// maybe - 2?, both seem to work?


    while(beginning < end){
        if(!((97 <= (int)*beginning) && ((int)*beginning <= 122))){
            beginning++;
            continue;
        }
        if(!((97 <= (int)*end) && ((int)*end <= 122))){
            end--;
            continue;
        }

        if (*beginning != *end) {
            return 1;
        }
    
        beginning++;
        end--;
    }
    return 0;
}