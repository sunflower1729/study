#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 50

int n, m;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int map[MAX + 2][MAX + 2] = {0};

typedef struct Queue{
    int x;
    int y;
    int value;
}Queue;

Queue q[10000];
int front = 0;
int rear = -1;

void push(int x, int y, int v){
    q[++rear] = (Queue){x, y, v};
}

Queue pop(){
    return q[front++];
}

int isempty(){
    return (front > rear);
}

void print_map(){
    printf("map");
    for(int i = 0; i < n+2; i++){
        for(int j = 0; j < m+2; j++){
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
        printf("\n");
    
}

int bfs(){
    int max_val = 0;
    int visit[MAX+2][MAX+2] = {0};
    while(!isempty()){
        Queue temp;
        temp = pop();
        visit[temp.y][temp.x] = 1;
        for(int i = 0; i < 4; i++){
            int nx = temp.x + dx[i];
            int ny = temp.y + dy[i];
            if(map[ny][nx] == 1 && visit[ny][nx] == 0){
                push(nx, ny, temp.value + 1);
                visit[ny][nx] = temp.value + 1;
                if(max_val < temp.value + 1){
                    max_val = temp.value + 1;
                }
            }
        }
        
        // for(int i = 0; i < n+1; i++){
        //     for(int j = 0; j < m+1; j++){
        //         printf("%d ", visit[i][j]);
        //     }
        //     printf("\n");
        // }
        // printf("\n");
    }
    return max_val;
}


int main(){
    (void)scanf(" %d %d", &n, &m);
    getchar();
    for(int i = 1; i < n+1; i++){
        for(int j = 1; j < m+1; j++){
            char c = getchar();
            if(c == 'W'){
                map[i][j] = 0;
            }
            else{
                map[i][j] = 1;
            }
        }
        char c = getchar(); //개행문자 제거
    }

    int d = 0;
    int max_d = 0;
    for(int i = 1; i < n+1; i++){
        for(int j = 1; j < m+1; j++){
            if(map[i][j] == 1){
                push(j, i, 0);
                d = bfs();
                if(d >= max_d){
                    max_d = d;
                }
                front = 0;
                rear = -1;
            }
        }
    }
    printf("%d", max_d);

}