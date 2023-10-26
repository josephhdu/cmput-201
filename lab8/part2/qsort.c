#include <stdio.h>
#include "quicksort.h"
#define N 10


int main(void){

    int a[N], i;
    int *low, *high;
    low = &a[0];
    high = &a[N - 1];

    printf("Enter %d numbers to be sorted: ", N);
    for(i = 0; i < N; i++)
        scanf("%d", &a[i]);

    quicksort(a, low, high);

    printf("In sorted order: ");
    for (i = 0; i < N; i++)
        printf("%d ", a[i]);

    printf("\n");

    return 0;
}