#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 100

int map[MAX + 2][MAX + 2] = { 0 };
int DP[MAX + 2][MAX + 2] = { 0 };
int n, m, a, b;

void print_map() {
    for (int i = n; i >= 1; i--)
    {
        for (int j = 1; j <= m; j++)
        {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_dp() {
    for (int i = n; i >= 1; i--)
    {
        for (int j = 1; j <= m; j++)
        {
            printf("%d ", DP[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

typedef struct point {
    int x;
    int y;
}Point;

Point p[101 * 101];
int cnt = 0;

int start_search(int sx, int sy, int ex, int ey) {

    DP[sx][sy] = 1;

    for (int i = sx; i <= ex; i++) {
        for (int j = sy; j <= ey; j++) {
            if (map[i][j] == -1) continue;
            if (i > sx) DP[i][j] = DP[i][j] + DP[i - 1][j];
            if (j > sy) DP[i][j] = DP[i][j] + DP[i][j - 1];
        }
    }
    //print_dp();
    return DP[ex][ey];
}

int main() {
    (void)scanf(" %d %d %d %d", &n, &m, &a, &b);
    for (int i = 0; i < a; i++)
    {
        int x, y;
        (void)scanf(" %d %d", &y, &x);
        map[y][x] = 1;
    }
    for (int i = 0; i < b; i++)
    {
        int x, y;
        (void)scanf(" %d %d", &y, &x);
        map[y][x] = -1;
    }

    if (map[1][1] == -1) {
        printf("0\n");
        return 0;
    }

    p[cnt++] = (Point){ 1, 1 };
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if(map[i][j] == 1)
                p[cnt++] = (Point){ i, j };
        }
    }
    p[cnt++] = (Point){ n, m };

    int answer = 1;
    for (int i = 0; i <= a; i++) {
        answer *= start_search(p[i].x, p[i].y, p[i+1].x, p[i+1].y);
    }
    printf("%d", answer);
    return 0;
}
