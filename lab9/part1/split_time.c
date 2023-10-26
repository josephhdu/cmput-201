#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int hours;
    int minutes;
    int seconds;
} time;

time split_time(long total_seconds);

int main(){

    long total_seconds;
    printf("Enter time as seconds since midnight: ");
    scanf("%ld", &total_seconds);

    if(total_seconds > 86399){
        fprintf(stderr,"Total time limit exceded\n");
        return 0;
    }

    time time1 = split_time(total_seconds);
    printf("Hours are %d, Minutes are %d, Seconds are %d\n", time1.hours, time1.minutes, time1.seconds);

}

time split_time(long total_seconds){
    int hr = total_seconds / 3600;
    total_seconds = total_seconds - (hr * 3600);

    int min = total_seconds / 60;
    total_seconds = total_seconds - (min * 60);

    int sec = total_seconds;

    time time1 = {.hours = hr, .minutes = min, .seconds = sec};
    return time1;
}