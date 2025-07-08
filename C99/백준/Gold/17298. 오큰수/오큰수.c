#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int stack[1000000] = {0};
int answer[1000000] = {0};

int ST[1000000] = {0};
int top = -1;

int isempty(){
    if(top > -1)
        return 0;
    return 1;
}

void push(int a){
    ST[++top] = a;
}



int main(){
    int n;
    (void)scanf(" %d", &n);

    for(int i = 0; i < n; i++){
        (void)scanf(" %d", &stack[i]);
    }
    
    for(int i = n-1; i > -1; i--){

        if(i == n-1){
            answer[i] = -1;
        }

        while(!isempty() && stack[i] >= ST[top]){
            top--;
            answer[i] = -1;
        }

        if(!isempty() && stack[i] <= ST[top]){
            answer[i] = ST[top];
        }

        push(stack[i]);
    }

    for(int i = 0; i < n; i++){
        printf("%d ", answer[i]);
    }
    
}
