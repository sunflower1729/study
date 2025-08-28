#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#define MAXN 1000000 + 1
#define MAXM 2000000*2 + 4

int N, M;

typedef struct Edge {
    int to;
    int next;
}Edge;

Edge edges[MAXM];
int head[MAXN];
int edge_cnt = 0;

void addEDGE(int from, int to, int cost) {
    edges[edge_cnt].to = to;
    edges[edge_cnt].next = head[from];
    head[from] = edge_cnt++;

    edges[edge_cnt].to = from;
    edges[edge_cnt].next = head[to];
    head[to] = edge_cnt++;
}

int visited[MAXN] = {0};
long long answer = 0;

void dfs(int pre_node, int curr_node){
    int i = head[curr_node];
    visited[curr_node] = visited[pre_node] + 1;
    while(1){
        if(i == -1) break;
        int next_node = edges[i].to;
        i = edges[i].next;
        if(next_node != pre_node){
            if(visited[next_node] != 0){ //cycle 발생
                if(visited[curr_node] > visited[next_node]){
                    long long cycle = visited[curr_node] - visited[next_node] + 1;
                    answer += cycle * cycle;
                }
            }
            else{
                dfs(curr_node, next_node);
            }
        }
    }
}

int main() {
    (void)scanf(" %d %d", &N, &M);
    for (int i = 0; i <= 2 * M + 1; i++) {
        head[i] = -1;
    }
    for (int i = 0; i < M; i++) {
        int a, b, c;
        (void)scanf(" %d %d %d", &a, &b, &c);
        addEDGE(a, b, c);
    }
    dfs(0, 1);
    printf("%lld\n", answer);
}