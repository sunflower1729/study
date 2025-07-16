#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 100

int n, m;
int rs_x, rs_y, rs_s;
int re_x, re_y, re_s;

int dx[5] = {0, 1, -1, 0, 0};
int dy[5] = {0, 0, 0, 1, -1};

int map[MAX + 2][MAX + 2] = {0};

typedef struct Queue {
    int x;
    int y;
    int value;
    int dir;
} Queue;

Queue q[100000];
int front = 0, rear = -1;

void push(int x, int y, int v, int d) {
    q[++rear] = (Queue){x, y, v, d};
}

Queue pop() {
    return q[front++];
}

int isempty() {
    return front > rear;
}

int turn_cost(int from, int to) {
    if (from == to) return 0;
    if ((from == 1 && to == 2) || (from == 2 && to == 1)) return 2;
    if ((from == 3 && to == 4) || (from == 4 && to == 3)) return 2;
    return 1;
}

void bfs(int sx, int sy, int s) {
    int visit[MAX + 2][MAX + 2][5] = {0};
    push(sx, sy, 0, s);
    visit[sy][sx][s] = 1;

    int answer = 2147483647;

    while (!isempty()) {
        Queue temp = pop();
        int x = temp.x, y = temp.y;
        int value = temp.value;
        int dir = temp.dir;

        if (x == re_x && y == re_y) {
            int cost = value + turn_cost(dir, re_s);
            if (cost < answer) {
                answer = cost;
            }
        }

        for (int i = 1; i <= 4; i++) {
            for (int k = 1; k <= 3; k++) {
                int nx = x + dx[i] * k;
                int ny = y + dy[i] * k;

                if (map[ny][nx] == 1) break; 

                int ncost = value + turn_cost(dir, i) + 1;
                if (visit[ny][nx][i] == 0 || visit[ny][nx][i] > ncost) {
                    visit[ny][nx][i] = ncost;
                    push(nx, ny, ncost, i);
                }
            }
        }
    }

    printf("%d\n", answer);
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n + 2; i++) {
        for (int j = 0; j < m + 2; j++) {
            map[i][j] = 1;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &map[i][j]);
        }
    }

    scanf("%d %d %d", &rs_y, &rs_x, &rs_s);
    scanf("%d %d %d", &re_y, &re_x, &re_s);

    if (rs_x == re_x && rs_y == re_y) {
        printf("%d\n", turn_cost(rs_s, re_s));
    } else {
        bfs(rs_x, rs_y, rs_s);
    }

    return 0;
}
