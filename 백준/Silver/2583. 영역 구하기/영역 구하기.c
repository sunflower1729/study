#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX 100

int map[101][101] = {0};
int visit[101][101] = {0};

int m, n, k;

void fill(int a, int b, int c, int d){
    for(int i = c; i < d; i++){
        for(int j = a; j < b; j++){
            map[i][j] = 1;
        }
    }
}

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

void dfs(int a, int b, int* num){
    visit[a][b] = 1;
    (*num)++;
    for(int i = 0; i < 4; i++){
        int nx = b + dx[i];
        int ny = a + dy[i];
        if(nx >= 0 && nx < n && ny >= 0 && ny < m){
            if(visit[ny][nx]==0 && map[ny][nx] ==0){
                dfs(ny, nx, num);
            }
        }
    }

}

int cmp(const void* a, const void* b){
    return (*(int*)a) - (*(int*)b);
}

int front, rear;

typedef struct {
    int y;
    int x;
}Node;

Node queue[101 * 101];

int bfs(int sy, int sx){
    front = rear = 0;
    queue[rear++] = (Node){sy, sx};
    visit[sy][sx] = 1;
    int area = 1;

    while (front < rear)
    {
        Node cur = queue[front++];
        for(int i = 0; i < 4; i++){
            int ny = cur.y + dy[i];
            int nx = cur.x + dx[i];

            if(ny >= 0 && nx >= 0 && ny < m && nx < n){
                if(visit[ny][nx] ==0 && map[ny][nx] == 0){
                    area++;
                    visit[ny][nx] = 1;
                    queue[rear++] = (Node){ny, nx};
                }
            }

        }
    }
    return area;
}

int main(){
    (void)scanf("%d %d %d", &m, &n, &k);

    for(int i = 0; i < k; i++){
        int x1, x2, y1, y2;
        (void)scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        fill(x1, x2, y1, y2);
    }

    int arears[MAX*MAX];
    int area_count = 0;

    for(int i = 0; i < m; i ++){
        for(int j = 0; j < n; j++){
            if(visit[i][j] == 0 && map[i][j] == 0){
                int area = bfs(i, j);
                arears[area_count++] = area;
            }
        }
    }

    qsort(arears, area_count, sizeof(int), cmp);
    printf("%d\n", area_count);
    for(int i = 0; i < area_count; i++){
        printf("%d", arears[i]);
        if (i < area_count - 1) printf(" ");
    }
    printf("\n");
}