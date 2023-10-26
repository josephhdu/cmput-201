#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

int main(){
    char stack[10];
    int top  = -1;
    char brace_str[999999];

    printf("Enter parantheses and/or braces: ");
    fgets(brace_str, 999999, stdin);

    int length = strlen(brace_str);

    for(int i = 0; i < length; i++){
        char brace = brace_str[i];


        if(brace != '(' && brace != ')' && brace != '{' && brace != '}'){
            continue;
        }

        if(i == 0){
            if(brace == ')'){ // check is first brace is ( or {
                printf("Parenthesis are not nested properly\n");
                return 0;
            }else if(brace == '}'){
                printf("Parenthesis are not nested properly\n");
                return 0;
            }
        }
        
        if(brace == '(' || brace == '{'){
            push(brace, stack, &top);

        } else if(brace == ')' || brace == '}'){
            if(brace == ')'){
                if(pop(stack, &top) != '('){
                    printf("Parenthesis are not nested properly\n");
                    return 0;
                }
            } else if(brace == '}'){
                if(pop(stack, &top) != '{'){
                    printf("Parenthesis are not nested properly\n");
                    return 0;
                }
            }
        }

    }

    printf("Parenthesis are nested properly\n");
}