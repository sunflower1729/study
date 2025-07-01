#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int T;
char phone[10000][11];
int len[10000];

//qsort의 배열을 정렬하기 위해 void로 호출 해야 한다.
//const void *a, const void *b를 사용함으로써 타입을 몰라도
//넘겨 줄 수 있다.
//또한 qsort의 compare의 형식이 (*compar)(const void *, const void *) 이기 때문
int compare(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}
int main(){
    (void)scanf(" %d", &T);
    while(T--){
        int n;
        int flag = 0;

        (void)scanf(" %d", &n);
        //입력 string의 길이를 배열에 넣는다.
        for(int i = 0; i < n; i++){
            (void)scanf(" %s", phone[i]);
            len[i] = strlen(phone[i]);
        }

        //정렬 시킨 후 다음 값하고만 비교하여 답을 찾는다.
        qsort(phone, n, sizeof(phone[0]), compare);
        for(int i = 0; i < n-1; i++){
            char str[11];
            if (strncmp(phone[i], phone[i+1], strlen(phone[i])) == 0){
                flag = 1;
                break;
            }
        }
        if(flag){
            printf("NO\n");
        }
        else{
            printf("YES\n");
        }
    }
}