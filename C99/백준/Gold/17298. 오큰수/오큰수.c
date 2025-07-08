/*
알고리즘 1
맨 뒤부터 검사한다
맨 뒤는 -1

앞으로 한칸씩
움직이면서 바로 다음 칸 수와 비교한다
다음 칸 수보다 작으면 다음 인덱스를 가져오고
크면 max값과 비교한다

max보다 크면 -1, max 값 새로 할당
작으면 해당 지점부터 max Index까지 비교한다


알고리즘 2
스택을 이용해서 검사
스택을 이용하면 O(2n)만큼의 시간이 걸린다.
이를 활용하여 해당 수가 top에 있는 값보다 크면 
더 큰 값이 나올 때 까지 top에서 뺀다.
만약 큰 값이 더이상 없으면 -1,
있으면 top 값이 할당되며
해당 수는 stack의 맨 위로 올라간다.
*/
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

/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int stack[1000000] = {0};
int answer[1000000] = {0};

int main(){
    int n;
    (void)scanf(" %d", &n);

    for(int i = 0; i < n; i++){
        (void)scanf(" %d", &stack[i]);
    }

    //초기 값 할당
    answer[0] = -1;
    int max = stack[n-1];
    int max_index = n-1;

    int max2 = 0;
    int max2_index = 0;

    for(int j = n-2; j != -1; j--){
        if(stack[j] < stack[j+1]){
            answer[n-j-1] = stack[j+1];
            if(max2 <= stack[j]){
                max2 = stack[j];
                max2_index = j;
            }
        }
        // else if(stack[j] == stack[j+1]){
        //     answer[n-j-1] = answer[n-j -2];
        // }
        else{
            if(max <= stack[j]){
                max2 = 0;
                max2_index = 0;
                answer[n-j-1] = -1;
                max = stack[j];
                max_index = j;
            }
            else{
                if(max2 <= stack[j]){
                    answer[n-j-1] = max;
                    max2 = stack[j];
                    max2_index = j;
                }
                else{
                    for(int k = j; k <= max2_index; k++){
                        if(stack[j] < stack[k]){
                            answer[n-j-1] = stack[k];
                            break;
                        }
                    }
                }
            }
        }
    }

    for(int i = n-1; i != -1; i--){
        printf("%d ", answer[i]);
    }
}

*/
