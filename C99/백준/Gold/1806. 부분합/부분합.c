#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX 100000
int N, S;
int arr[MAX + 1];

int main(){
    (void)scanf(" %d %d", &N, &S);

    for(int i = 0; i < N; i++){
        (void)scanf(" %d", &arr[i]);
    }

    int front = 0;
    int rear = 0;

    int sum = 0;
    int answer = MAX + 10;
    
    while(front != N){
        if(sum < S && rear != N){
            sum += arr[rear++];
        }
        else{
            if((rear - front + 1)  <= answer && sum >= S){
                answer = rear - front;
            }
            sum -= arr[front++];
        }
    }
    if(answer == MAX+10){
        printf("0");
    }
    else{
        printf("%d", answer);
    }
}