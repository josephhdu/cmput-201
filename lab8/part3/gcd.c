#include <stdio.h>

int gcd(int m, int n);

int main(){
    int m, n;

    printf("Enter two Intergers: ");
    scanf("%d", &m);
    scanf("%d", &n);

    int answer = gcd(m, n);

    printf("Greatest common divisor: %d\n", answer);

}

int gcd(int m, int n){
    if (n == 0){
        return m;
    } else{
        return gcd(n, m % n);
    }
    
}