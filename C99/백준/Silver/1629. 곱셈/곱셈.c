#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

long long a, b, c;

long long recursion(int n){
    if(n == 1){
        return a % c;
    }
    long long x = recursion(n/2);
    x = (x * x) % c;
    if(n % 2){
        x = x * a % c;
        return x;
    }
    return x;
}


int main(void){
    (void)scanf("%d %d %d", &a, &b, &c);

    int answer;
    answer = recursion(b);
    printf("%d", answer);
}