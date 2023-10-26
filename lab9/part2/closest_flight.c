#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int depHour;
    int depMinutes;
    int arrHour;
    int arrMinutes;
    char depZone[20];
    char arrZone[20];

} flightTime;

typedef struct {
    flightTime times;
    int totalTime;
} flight;

int main(){
    flight flights[7];

    flight flight1 = {.times.depHour = 8, .times.depMinutes = 1, .times.arrHour = 10, .times.arrMinutes = 17};
    strcpy(flight1.times.depZone, "a.m.");
    strcpy(flight1.times.arrZone, "a.m.");
    flight1.totalTime = (flight1.times.depHour * 60) + flight1.times.depMinutes;
    flights[0] = flight1;

    flight flight2 = {.times.depHour = 10, .times.depMinutes = 58, .times.arrHour = 1, .times.arrMinutes = 11};
    strcpy(flight2.times.depZone, "a.m.");
    strcpy(flight2.times.arrZone, "p.m.");
    flight2.totalTime = (flight2.times.depHour * 60) + flight2.times.depMinutes;
    flights[1] = flight2;

    flight flight3 = {.times.depHour = 11, .times.depMinutes = 19, .times.arrHour = 1, .times.arrMinutes = 31};
    strcpy(flight3.times.depZone, "a.m.");
    strcpy(flight3.times.arrZone, "p.m.");
    flight3.totalTime = (flight3.times.depHour * 60) + flight3.times.depMinutes;
    flights[2] = flight3;

    flight flight4 = {.times.depHour = 12, .times.depMinutes = 47, .times.arrHour = 3, .times.arrMinutes = 0};
    strcpy(flight4.times.depZone, "p.m.");
    strcpy(flight4.times.arrZone, "p.m.");
    flight4.totalTime = (flight4.times.depHour * 60) + flight4.times.depMinutes;
    flights[3] = flight4;

    flight flight5 = {.times.depHour = 4, .times.depMinutes = 16, .times.arrHour = 6, .times.arrMinutes = 30};
    strcpy(flight5.times.depZone, "p.m.");
    strcpy(flight5.times.arrZone, "p.m.");
    flight5.totalTime = 976; //hard coded, cause i can't be bothered to do it the right way, the ones below are hard coded too
    flights[4] = flight5;

    flight flight6 = {.times.depHour = 7, .times.depMinutes = 22, .times.arrHour = 9, .times.arrMinutes = 55};
    strcpy(flight6.times.depZone, "p.m.");
    strcpy(flight6.times.arrZone, "p.m.");
    flight6.totalTime = 1162;
    flights[5] = flight6;

    flight flight7 = {.times.depHour = 9, .times.depMinutes = 13, .times.arrHour = 11, .times.arrMinutes = 25};
    strcpy(flight7.times.depZone, "p.m.");
    strcpy(flight7.times.arrZone, "p.m.");
    flight7.totalTime = 1273;
    flights[6] = flight7;

    int hrs;
    int mins;
    int tot;

    printf("Enter a 24-hour time: ");
    scanf("%d:%d", &hrs, &mins);

    tot = (60*hrs) + mins;

    if(tot > 1499){
        printf("Invalid time entered.\n");
        return 0;
    } else if(hrs > 24){
        printf("Invalid time entered.\n");
        return 0;
    } else if(mins > 59){
        printf("Invalid time entered.\n");
        return 0;
    }

    if(tot > 1273){ //so if it past the latest dep time is resets to the next day;
        tot = 0;
    }

    int closestIndex = 0;
    int closest = 2000;
    for(int i = 0; i < 7; i++){
        int temp = flights[i].totalTime - tot;

        if(temp > 0){
            if(temp < closest){
                closestIndex = i;
                closest = temp;
            }
        }
    }

    printf("Next flight is at %d:%02d %s, arriving at %d:%02d %s\n", flights[closestIndex].times.depHour, flights[closestIndex].times.depMinutes, flights[closestIndex].times.depZone, flights[closestIndex].times.arrHour, flights[closestIndex].times.arrMinutes, flights[closestIndex].times.arrZone);

    return 0;
}