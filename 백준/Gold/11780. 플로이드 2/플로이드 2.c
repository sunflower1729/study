#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#define MAX 101
#define INF 100000 * 100 + 1

int N, M;
int cost[MAX][MAX] = {0};
int to_destination[MAX][MAX] = {0};

void PRINT_COST(){
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            if(cost[i][j] == INF ){
                printf("0 ");
            }
            else{
                printf("%d ", cost[i][j]);
            }
        }
        printf("\n");
    }
}

void PRINT_ROUTE(){
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            printf("%10d ", to_destination[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("\n");
}

void INIT_COST(){
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            cost[i][j] = INF;
        }
    }
}

void FIND_COST(){
    for(int k = 1; k <= N; k++){
        for(int i = 1; i <= N; i++){
            for(int j = 1; j <= N; j++){
                if(i == j) continue;
                if(j == k) continue;
                if(k == i) continue;
                if(cost[i][j] < cost[i][k] + cost[k][j]) continue;
                else{
                    cost[i][j] = cost[i][k] + cost[k][j];
                    to_destination[i][j] = k;
                }
            }
        }
    }
}

void FIND_ROUTE(){
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            
            if(cost[i][j] == INF){
                printf("0\n");
                continue;
            }

            int answer[100];
            int answer_pnt = 0;
            int k = j;
            int l = i;
            answer[answer_pnt++] = i;
            int cnt = 0;
            while(to_destination[l][k] != k){
                while(to_destination[l][k] != k){
                    k = to_destination[l][k];
                }
                answer[answer_pnt++] = k;
                l = to_destination[l][k];
                k = j;
            }
            answer[answer_pnt++] = j;
            printf("%d ", answer_pnt);
            for(int pnt = 0; pnt < answer_pnt; pnt++){
                printf("%d ", answer[pnt]);
            }
            printf("\n");
        }
    }
}

int main(){
    (void)scanf(" %d", &N);
    (void)scanf(" %d", &M);
    
    INIT_COST();

    for(int i = 0; i < M; i++){
        int a, b, v;
        (void)scanf(" %d %d %d", &a, &b, &v);
        if(v < cost[a][b]) cost[a][b] = v;
        to_destination[a][b] = b;
    }

    FIND_COST();
    PRINT_COST();
    FIND_ROUTE();
}