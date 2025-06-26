#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX 40
int fix_seat[MAX + 1] = { 0 };
int nonefix_seat_cnt[MAX + 1] = {0};
int fibo[MAX+1] = {1, 1, 2, 3};

int fibonacci(int n){
    if(fibo[n] == 0){
        fibo[n] = fibonacci(n-1) + fibonacci(n-2);
    }
    return fibo[n];
}


int main()
{
    int N, M;
    (void)scanf(" %d", &N);
    (void)scanf(" %d", &M);

    for(int i = 0; i < M; i++){
        (void)scanf(" %d", &fix_seat[i]);
    }

    for(int i = 0; i < M; i++){
        if(i == 0)
            nonefix_seat_cnt[i] = fix_seat[i] - 1;
        else{
            nonefix_seat_cnt[i] = fix_seat[i] - fix_seat[i-1] - 1;            
        }
    }  
    
    nonefix_seat_cnt[M] = N - fix_seat[M - 1];

    int answer = 1;
    for(int i = 0; i <= M; i++){
        if(fibo[nonefix_seat_cnt[i]] == 0){
            fibonacci(nonefix_seat_cnt[i]);
        }
        answer *= fibo[nonefix_seat_cnt[i]];
    }
    printf("%d", answer);
    
    return 0;
}
