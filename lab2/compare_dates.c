#include <stdio.h>
#include <stdlib.h>

int main(){

    FILE *file;
    file = fopen("input_date.txt", "r");

    int year, month, date, fyear, fmonth, fdate;

    printf("Enter date to compare to (mm/dd/yy): ");
    scanf("%d/%d/%d", &month, &date, &year);

    if (month < 1 || month > 12){
        printf("Wrong date format");
        exit(4);
    }

    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
        if (date < 1 || date > 31){
        printf("Wrong date format");
        exit(4);
        }
    }
    if (month == 4 || month == 6 || month == 9 || month == 11){
        if (date < 1 || date > 30){
        printf("Wrong date format");
        exit(4);
        }
    }  
    if (month == 2){
        if (date < 1 || date > 28){
        printf("Wrong date format");
        exit(4);
        }
    }

    if (year < 1 || year > 99){
        printf("Wrong date format");
        exit(4);
    }

    fscanf(file, " %d/ %d/ %d", &fmonth, &fdate, &fyear);

    int earlier = 0;

    if (fyear <= year){
        if (fyear == year){
            if (fmonth <= month){
                if (fmonth == month){
                    if (fdate <= date){
                        if (fdate == date){
                            printf("They are the same date");
                            return 0;
                        }
                    }
                    else{
                        earlier = 1;
                    }
                }
            }
            else{
                earlier = 1;
            }
        }
    }
    else{
        earlier = 1;
    }

    if (earlier == 0){
        printf("%d/%d/%02d is earlier than %d/%d/%2d", fmonth, fdate, fyear, month, date, year);
    }
    else{
        printf("%d/%d/%02d is later than %d/%d/%02d", fmonth, fdate, fyear, month, date, year);
    }

    fclose(file);
}