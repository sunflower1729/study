#include <stdio.h>
#include <string.h>

typedef struct {
    int to, cost, next;
} Edge;

Edge edges[200000]; 
int head[100001];
int edgeCount = 0;

int V;
int cnt = 0;

void addEdge(int from, int to, int cost) {
    edges[edgeCount].to = to;
    edges[edgeCount].cost = cost;
    edges[edgeCount].next = head[from];
    head[from] = edgeCount++;
}

int bfs(int start) {
    int visited[100001] = {0};
    int dist[100001] = {0};

    int queue[100001];
    int front = 0, rear = 0;

    queue[rear++] = start;
    visited[start] = 1;

    int farNode = start;

    while (front < rear) {
        int cur = queue[front++];
        for (int i = head[cur]; i != -1; i = edges[i].next) {
            int nxt = edges[i].to;
            if (!visited[nxt]) {
                visited[nxt] = 1;
                dist[nxt] = dist[cur] + edges[i].cost;
                queue[rear++] = nxt;
                if (dist[nxt] > dist[farNode]) {
                    farNode = nxt;
                }
            }
        }
    }
    if(cnt == 1) printf("%d\n", dist[farNode]);
    return farNode;
}

int main() {
    scanf("%d", &V);
    memset(head, -1, sizeof(head));

    for (int i = 0; i < V; i++) {
        int from;
        scanf("%d", &from);
        while (1) {
            int to, cost;
            scanf("%d", &to);
            if (to == -1) break;
            scanf("%d", &cost);
            addEdge(from, to, cost);
        }
    }

    int far1 = bfs(1);
    cnt = 1;
    int far2 = bfs(far1);

    return 0;
}
