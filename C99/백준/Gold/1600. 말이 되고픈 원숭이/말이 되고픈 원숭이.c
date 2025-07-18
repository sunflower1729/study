#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 200

//map의 테두리를 +2 만큼 늘려 bfs시 조건을 줄임
int map[MAX+4][MAX+4];
int visit[MAX+4][MAX+4][31];

int dx[12] = {1, -1, 0, 0, 1, 2, 1, 2, -1, -2, -1, -2};
int dy[12] = {0, 0, 1, -1, 2, 1, -2, -1, 2, 1, -2, -1};

int W, H;
int K;

void print_map(){
    for(int i = 2; i < H + 2; i++){
        for(int j = 2; j < W + 2; j++){
            printf("%3d", map[i][j]);
        }
        printf("\n");
    }
}

typedef struct Queue{
    int x;
    int y;
    int k_cnt;
}Queue;

Queue q[MAX * MAX * MAX] = {0};
int front = 0, rear = -1;

void push(int x, int y, int k){
    q[++rear] = (Queue){x, y, k};
}

Queue pop(){
    return q[front++];
}

int bfs(){
    push(2, 2, K);
    for(int i = 0; i < K + 1; i++){
        visit[2][2][i] = 1;
    }
    if(H == 1 && W == 1){
        return 0;
    }
    while(front <= rear){
        Queue temp = pop();
        if(temp.x == 6 && temp.y == 6 && temp.k_cnt == 1){
        }
        for(int i = 0; i < 12; i++){
            int nx = temp.x;
            int ny = temp.y;
            int k_cnt = temp.k_cnt;
            nx += dx[i];
            ny += dy[i];
            if(map[ny][nx] == 0) continue;

            if(i >= 4){
                if(!k_cnt) break;
                if(!visit[ny][nx][k_cnt - 1] || visit[ny][nx][k_cnt - 1] > visit[temp.y][temp.x][k_cnt] + 1)
                {
                    k_cnt--;
                    visit[ny][nx][k_cnt] = visit[temp.y][temp.x][k_cnt + 1] + 1;
                    push(nx, ny, k_cnt);
                }
            }
            else{
                if(!visit[ny][nx][k_cnt] || visit[ny][nx][k_cnt] > visit[temp.y][temp.x][k_cnt] + 1){
                    visit[ny][nx][k_cnt] = visit[temp.y][temp.x][k_cnt] + 1;
                    push(nx, ny, k_cnt);
                }
            }
            if(nx == W+1 && ny == H+1){
                return visit[ny][nx][k_cnt] - 1;
            }

        }

        // for(int k = 0; k < K + 1; k++){
        //     printf("%d \n", k);
        //     for(int i = 2; i < H + 2; i++){
        //         for(int j = 2; j < W + 2; j++){
        //             printf("%3d", visit[i][j][k]);
        //         }
        //         printf("\n");
        //     }
        //     printf("\n");
        // }

    }

    return -1;
}



int main(){

    (void)scanf(" %d", &K);
    (void)scanf(" %d %d", &W, &H);

    for(int i = 2; i < H + 2; i++){
        for(int j = 2; j < W + 2; j++){
            int input;
            (void)scanf(" %d", &input);
            if(input) map[i][j] = 0; // 0 = 벽, 1 = 가능
            else map[i][j] = 1;
        }
    }

    int answer = bfs();
    printf("%d", answer);
}