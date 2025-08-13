#include <stdio.h>

int N, M;
int com[100][100] = { 0 };
int virus[100] = {1,};

int main(){
    (void)scanf(" %d", &N);
    (void)scanf(" %d", &M);
    for(int i = 0; i < M; i++){
        int a, b;
        (void)scanf(" %d %d", &a, &b);
        com[a-1][b-1] = 1;
        com[b-1][a-1] = 1;
    }

    int answer = 0;

    for(int k = 0; k < N; k++){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(i == j) continue;
                if(com[i][k] + com[k][j] == 2){
                    com[i][j] = 1;
                }
            }
        }
    }

    for(int i = 0; i < N; i++){
        answer+=com[0][i];
    }

    printf("%d", answer);
}