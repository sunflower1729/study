#include <stdio.h>
#define MAX 100

int N, M;
int sx, sy, ex, ey;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

typedef struct dino{
    int x;
    int y;
    int time;
}Dino;

Dino dino[MAX*MAX*50 + 3];
int front = 0, rear = -1;

int map[MAX][MAX];
int visit[3][MAX][MAX];

void push(int x, int y, int time){
    dino[++rear] = (Dino){x, y, time};
}

Dino pop(){
    return dino[front++];
}

void print_map(){
    for(int k = 0; k < 3; k++){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                printf("%9d ", visit[k][i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    printf("\n");
    printf("\n");
}


void find_route(){
    while(rear >= front){
        Dino temp = pop();
        int x = temp.x;
        int y = temp.y;
        int time = temp.time % 3;

        int i = 0, j = 4;
        if(time == 0){
        }
        else if (time == 1){
            j = 2;
        }
        else{
            i = 2;
        }

        for(; i < j; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx < 0 || ny < 0 || nx >= N || ny >= M) continue;
            if(map[nx][ny] == -1) continue;
            if(visit[(time + 1)%3][nx][ny] > visit[time][x][y] + map[nx][ny]){
                visit[(time + 1)%3][nx][ny] = visit[time][x][y] + map[nx][ny];
                push(nx, ny, temp.time + 1);
            }
        }
        //print_map();
    }

    int answer = 0xfffffff;
    for(int i = 0; i < 3; i++){
        if(visit[i][ex-1][ey-1] < answer)
            answer = visit[i][ex-1][ey-1];
    }
    if(answer == 0xfffffff){
        answer = -1;
    }

    printf("%d", answer);
}


int main(){
    (void)scanf("%d %d", &N, &M);
    //x means row, y means col
    (void)scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
    
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            int v;
            (void)scanf(" %d", &v);
            map[i][j] = v;
        }
    }
    
    for(int k = 0; k < 3; k++){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                visit[k][i][j] = 0xfffffff;
            }
        }
    }

    push(sx - 1, sy - 1, 1);
    visit[1][sx-1][sy-1] = 0;

    find_route();
}