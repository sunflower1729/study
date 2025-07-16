#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 100

int n;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int map[MAX + 2][MAX + 2] = {0};

typedef struct Queue{
    int x;
    int y;
}Queue;

Queue q[10000];
int front = 0;
int rear = -1;

void push(int x, int y){
    q[++rear] = (Queue){x, y};
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
        for(int j = 0; j < n+2; j++){
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
        printf("\n");
    
}

int bfs(int high){
    
    int cnt = 0;
    int rain = 0;
    int max_value = 0;


    while(1){
        int visit[MAX+2][MAX+2] = {0};
        for(int i = 1; i < n+1; i++){
            for(int j = 1; j < n+1; j++){
                if(map[i][j] > rain && visit[i][j] == 0){
                    push(j, i);

                    visit[i][j] = 1;
                    while(!isempty()){
                        Queue temp;
                        temp = pop();
                        for(int i = 0; i < 4; i++){
                            int nx = temp.x + dx[i];
                            int ny = temp.y + dy[i];
                            if(map[ny][nx] > rain && visit[ny][nx] == 0){
                                push(nx, ny);
                                visit[ny][nx] = 1;
                            }
                        }
                    }

                    front = 0;
                    rear = -1;
                    cnt++;
                }
            }
        }
        if(max_value < cnt){
            max_value = cnt;
        }
        if(high == rain){
            break;
        }
        cnt = 0;
        rain++;
    }

    return max_value;
}


int main(){
    (void)scanf(" %d", &n);
    getchar();
    int high = 0;
    for(int i = 1; i < n+1; i++){
        for(int j = 1; j < n+1; j++){
            int v;
            (void)scanf(" %d", &v);
            map[i][j] = v;
            if(v > high) high = v;
        }
    }

    int cnt = bfs(high);
    printf("%d", cnt);

}