#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAXN 101       // 배열 편의상 1..100 사용, stride = 101
#define MAXROOM (MAXN * MAXN)
#define MAXM 20005

int N, M;

// 스위치 인접리스트: 한 방에서 켤 수 있는 (a,b)들을 저장
int head[MAXROOM];
int tox[MAXM], toy[MAXM], nxt[MAXM];
int sw_idx = 0;

int q[MAXROOM];
int front_q, rear_q;

int light[MAXN][MAXN];   // 1 = 불 켜짐
int visit[MAXN][MAXN];   // 1 = 방문(실제로 갈 수 있었음)

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

// (x,y) -> id
static inline int id(int x, int y){
    return y * MAXN + x;
}

void add_switch(int x, int y, int a, int b){
    int from = id(x,y);
    tox[sw_idx] = a;
    toy[sw_idx] = b;
    nxt[sw_idx] = head[from];
    head[from] = sw_idx++;
}

void push_q(int x, int y){
    q[rear_q++] = id(x,y);
}

int main(){
    // init
    for(int i=0;i<MAXROOM;i++) head[i] = -1;

    if(scanf("%d %d", &N, &M) != 2) return 0;
    for(int i=0;i<M;i++){
        int x,y,a,b;
        scanf("%d %d %d %d", &x, &y, &a, &b);
        add_switch(x,y,a,b);
    }

    // 초기
    for(int i=0;i<MAXN;i++){
        for(int j=0;j<MAXN;j++){
            light[i][j] = 0;
            visit[i][j] = 0;
        }
    }

    front_q = 0; rear_q = 0;
    light[1][1] = 1;    // (1,1) 불 켜짐
    visit[1][1] = 1;    // (1,1) 방문 가능(출발)
    push_q(1,1);

    int ans = 1; // (1,1) 포함

    // BFS
    while(front_q < rear_q){
        int cur = q[front_q++];
        int cx = cur % MAXN;
        int cy = cur / MAXN;

        // 이 방에서 켤 수 있는 모든 스위치 처리
        for(int e = head[cur]; e != -1; e = nxt[e]){
            int tx = tox[e];
            int ty = toy[e];
            if(light[ty][tx]) continue; // 이미 켜져있음

            light[ty][tx] = 1; // 새로 불 켬
            ans++;

            // 새로 켜진 방이 현재 방문 가능성이 생겼는지(이미 인접에 방문한 방이 있는지) 확인
            for(int d=0; d<4; d++){
                int ax = tx + dx[d];
                int ay = ty + dy[d];
                if(ax < 1 || ay < 1 || ax > N || ay > N) continue;
                if(visit[ay][ax]){ // 인접한 어떤 방문된 방이 있으면 즉시 이동 가능
                    visit[ty][tx] = 1;
                    push_q(tx, ty);
                    break;
                }
            }
        }

        // 인접한 방으로 이동 시도 (불이 켜져있고 아직 방문하지 않았다면)
        for(int d=0; d<4; d++){
            int nx = cx + dx[d];
            int ny = cy + dy[d];
            if(nx < 1 || ny < 1 || nx > N || ny > N) continue;
            if(visit[ny][nx]) continue;   // 이미 방문
            if(!light[ny][nx]) continue;  // 불 꺼져있으면 못감
            visit[ny][nx] = 1;
            push_q(nx, ny);
        }
    }

    printf("%d\n", ans);
    return 0;
}
