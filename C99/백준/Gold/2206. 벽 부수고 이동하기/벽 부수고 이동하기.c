#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#define MAX 1000
#define INF 2147483647

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int map[MAX][MAX] = {0};
int dp[2][MAX][MAX] = {0};

int N, M;

typedef struct Queue{
    int x;
    int y;
    int attack;
}Queue;

Queue q[MAX * MAX * 4 * 3] = {0};
int front = 0, rear = -1;

void push(Queue newnode){
    q[++rear] = newnode;
}

Queue pop(){
    return q[front++];
}

void init_dp(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            dp[0][i][j] = INF;
            dp[1][i][j] = INF;
        }
    }
}

int dfs(){
    if(N == 1 && M == 1)
        return 1;
    init_dp();
    push((Queue){0, 0, 1});

    dp[1][0][0] = 1;
    dp[0][0][0] = 1;

    while(rear >= front){
        Queue temp = pop();
        int x = temp.x;
        int y = temp.y;
        int attack = temp.attack;

        for(int i = 0; i < 4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx < 0 || ny < 0 || ny > N || nx > M) continue;
            
            if(map[ny][nx] == 1){
                if(attack){
                    if(dp[attack][y][x] + 1 < dp[attack-1][ny][nx]){
                        dp[attack-1][ny][nx] = dp[attack][y][x] + 1;
                        push((Queue){nx, ny, attack-1});
                    }
                }
                continue;
            }
            
            if(dp[attack][y][x] + 1 < dp[attack][ny][nx]){
                dp[attack][ny][nx] = dp[attack][y][x] + 1;
                push((Queue){nx, ny, attack});
            }

            if(ny == N-1 && nx == M-1){
                return dp[0][ny][nx] < dp[1][ny][nx] ? dp[0][ny][nx] : dp[1][ny][nx];
            }
        }
        
    }
    return -1;
}

int main(){
    (void)scanf(" %d %d", &N, &M);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            int c;
            (void)scanf("%1d", &c);
            if(c) map[i][j] = 1;
        }
    }

    int answer = dfs();
    printf("%d", answer);

}