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
앞에서 부터 검사한다
맨 앞의 수는 MAX 값으로 하고
MAX_INDEX를 설정한다

비교할 때 MAX보다 작은 값이 나오면
MIN, MIN_INDEX로 설정한다

비교할 때 MIN보다 작은 값이 나오면
MIN을 새로운 값으로 재할당한다

MIN보다 크고 MAX보다 작은 값이 나오면
MIN~

생각해보니까 이거 이렇게하면 반복문이 더 많아짐

*/

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