#define _CRT_NO_SECURE_WARNINGS

#include <stdio.h>

int input_data[80000];

long long answer[80000];

int top = -1;

typedef struct stack{
    int n;
    int w;
}Stack;

Stack stack[80000];

void push(Stack s){
    stack[++top] = s;
}

Stack pop(){
    return stack[top--];
}

int main(){
    int N;
    (void)scanf(" %d", &N);
    for(int i = 0; i < N; i++){
        (void)scanf(" %d", &input_data[i]);
    }

    int max = 0;
    int cnt = 0;
    int ans = 0;

    for(int i = N-1; i >= 0; i--){

        while(top > -1 && stack[top].n < input_data[i]){
            cnt += stack[top].w + 1;
            top--;
        }
        
        push((Stack){input_data[i], cnt});
        ans += cnt;
        cnt = 0;
    }
    printf("%lld", ans);
}