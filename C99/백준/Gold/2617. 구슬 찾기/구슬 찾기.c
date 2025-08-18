#define _CRT_NO_SECURE_WARNINGS
#include <stdio.h>

int N, M;
//1 means lose, 2 means win
int result[100][100] = {0};

void find_answer(){
    int answer = 0;
    for(int i = 1; i <= N; i++){
        int cnt1 = 0, cnt2 = 0;
        for(int j = 1; j <= N; j++){
            if(result[i][j] == 1) cnt1++;
            if(result[i][j] == 2) cnt2++;
        }
        if(cnt1 > N / 2 || cnt2 > N / 2) answer++;
    }

    printf("%d", answer);
}

void find(){
    for(int k = 1; k <= N; k++){
        for(int i = 1; i <= N; i++){
            for(int j = 1; j <= N; j++){
                if(result[k][i] * result[k][j] == 2){
                    result[i][j] = result[k][j];
                    result[j][i] = 3 - result[i][j];
                }
            }
        }
    }
    find_answer();
}


int main(){
    (void)scanf("%d %d", &N, &M);
    for(int i = 0; i < M; i++){
        int a, b;
        (void)scanf("%d %d", &a, &b);
        result[a][b] = 2;
        result[b][a] = 1;
    }
    find();
}