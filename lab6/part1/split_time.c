#include <stdio.h>
#include <stdlib.h>

//add cases,(neg num), (more than 1 input), (no int entered)

void split_time(long total_sec, int *hr, int *min, int *sec);

int main(int argc, char *argv[]){

    long total_sec = atoi(argv[1]);

    if(total_sec > 86399){
        fprintf(stderr,"Total time limit exceded\n");
        return 0;
    }

    int hr, min, sec;

    split_time(total_sec, &hr, &min, &sec);

    printf("Converted time = %02d:%02d:%02d\n", hr, min, sec);

}

void split_time(long total_sec, int *hr, int *min, int *sec){    
    *hr = total_sec / 3600;
    total_sec = total_sec - (*hr * 3600);

    *min = total_sec / 60;
    total_sec = total_sec - (*min * 60);

    *sec = total_sec;
}