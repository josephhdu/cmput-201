#include <stdio.h>

int main(void){
    int input, twenty, ten, five, one, current;
    printf("Enter a dollar amount:");
    scanf("%d", &input);

    twenty = input / 20;
    current = input % 20;
    ten = current / 10;
    current = input % 10;
    five = current / 5;
    current = input % 5;
    one = current / 1;

    printf("$20 bills: %d\n", twenty);
    printf("$10 bills: %d\n", ten);
    printf("$5 bills: %d\n", five);
    printf("$1 bills: %d\n", one);

}