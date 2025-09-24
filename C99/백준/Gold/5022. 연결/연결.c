#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int N, M;
int A1_x, A1_y, A2_x, A2_y, B1_x, B1_y, B2_x, B2_y;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int map[101][101] = {0};
int visited[101][101] = {0};

typedef struct queue{
    int x;
    int y;
}Queue;

Queue q[100*100 + 5];
int front, rear;

Queue parents[101][101] = {0, 0};

void push(Queue temp){
    q[++rear] = temp;
}

Queue pop(){
    return q[front++];
}

int answer1, answer2;
int bfs(int x1, int y1, int x2, int y2){
    front = 0;
    rear = -1;
    push((Queue){x1, y1});
    visited[x1][y1] = 1;
    parents[x1][y1] = (Queue){-1, -1};
    while(front <= rear){
        Queue temp = pop();
        int x = temp.x;
        int y = temp.y;

        if(x == x2 && y == y2){
            return visited[x][y] - 1;
        }
        for(int i = 0; i < 4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx < 0 || ny < 0 || nx > N || ny > M) continue;
            if(map[nx][ny] != 0) continue;
            if(visited[nx][ny] >= 1) continue;
            visited[nx][ny] = visited[x][y] + 1;
            push((Queue){nx, ny});
            parents[nx][ny] = (Queue){x, y};
        }
    }
    return 1000000;
}

void make_wall(int x1, int y1){
    map[x1][y1] = 1;
    Queue temp = parents[x1][y1];
    while(temp.x != -1){
        map[temp.x][temp.y] = 1;
        temp = parents[temp.x][temp.y];
    }
}



int main(){
    (void)scanf("%d %d", &N, &M);
    (void)scanf("%d %d", &A1_x, &A1_y);
    (void)scanf("%d %d", &A2_x, &A2_y);
    (void)scanf("%d %d", &B1_x, &B1_y);
    (void)scanf("%d %d", &B2_x, &B2_y);

    int ans1, ans2, ans3, ans4;

    map[B1_x][B1_y] = 1;
    map[B2_x][B2_y] = 1;
    ans1 = bfs(A1_x, A1_y, A2_x, A2_y);
    for(int i = 0; i <= N; i++){
        for(int j = 0; j <= M; j++){
            visited[i][j] = 0;
        }
    }
    make_wall(A2_x, A2_y);
    map[B1_x][B1_y] = 0;
    map[B2_x][B2_y] = 0;
    ans2 = bfs(B1_x, B1_y, B2_x, B2_y);

    for(int i = 0; i <= N; i++){
        for(int j = 0; j <= M; j++){
            visited[i][j] = 0;
        }
    }
    for(int i = 0; i <= N; i++){
        for(int j = 0; j <= M; j++){
            //printf("%d ", map[i][j]);
            map[i][j] = 0;
        }
        //printf("\n");
    }

    map[A1_x][A1_y] = 1;
    map[A2_x][A2_y] = 1;
    ans4 = bfs(B1_x, B1_y, B2_x, B2_y);
    for(int i = 0; i <= N; i++){
        for(int j = 0; j <= M; j++){
            visited[i][j] = 0;
        }
    }
    make_wall(B2_x, B2_y);
    map[A1_x][A1_y] = 0;
    map[A2_x][A2_y] = 0;
    ans3 = bfs(A1_x, A1_y, A2_x, A2_y);

    if(ans1 + ans2 >= 1000000 && ans3 + ans4 >= 1000000){
        printf("IMPOSSIBLE");
    }
    else if(ans1 + ans2 < ans3 + ans4){
        printf("%d", ans1 + ans2);
    }
    else{
        printf("%d", ans3 + ans4);
    }
}