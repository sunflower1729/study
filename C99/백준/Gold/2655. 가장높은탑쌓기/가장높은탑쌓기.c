#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N;

int box[100][100] = { 0 }; //제한 높이, 제한 무게
int box_point[100][100] = { 0 }; //해당 제한에 쌓인 박스 수
int box_top[100][100][100] = { 0 }; //쌓은 박스

typedef struct brick {
    int num;
    int w;
    int h;
    int t;
}Brick;

Brick brick[100];

int cmp_by_w(const void* a, const void* b) {
    const Brick* b1 = (const Brick*)a;
    const Brick* b2 = (const Brick*)b;
    return b1->w - b2->w;
}
int cmp_by_t(const void* a, const void* b) {
    const Brick* b1 = (const Brick*)a;
    const Brick* b2 = (const Brick*)b;
    return b1->t - b2->t;
}

int weightLIST[100] = { 0 };
int tonLIST[100] = { 0 };

void InitLIST() {
    qsort(brick, N, sizeof(Brick), cmp_by_t);
    for (int i = 0; i < N; i++) {
        tonLIST[i] = brick[i].t;
    }
    qsort(brick, N, sizeof(Brick), cmp_by_w);
    for (int i = 0; i < N; i++) {
        weightLIST[i] = brick[i].w;
    }
}

void findANS() {
    
    for (int i = 0; i < N; i++) {
        if (brick[0].t <= tonLIST[i]) {
            box[0][i] = brick[0].h;
            box_top[0][i][box_point[0][i]++] = 0;
        }
    }

    for (int i = 1; i < N; i++) {
        for (int j = 0; j < N; j++) {
            box[i][j] = box[i - 1][j];
            memcpy(box_top[i][j], box_top[i - 1][j], (box_point[i - 1][j] + 1) * sizeof(int));
            box_point[i][j] = box_point[i - 1][j];

            if (brick[i].t >= tonLIST[j] && brick[i].t == tonLIST[j]) {
                box[i][j] += brick[i].h;
                box_top[i][j][box_point[i][j]++] = i;
            }
            if(j >= 1 && box[i][j] < box[i][j-1]){
                box[i][j] = box[i][j-1];
                memcpy(box_top[i][j], box_top[i][j - 1], (box_point[i][j-1] + 1) * sizeof(int));
                box_point[i][j] = box_point[i][j - 1];
            }
        }
    }
    printf("%d\n", box_point[N-1][N-1]);
    for(int i = 0; i < box_point[N-1][N-1]; i++) {
        printf("%d\n", brick[box_top[N-1][N-1][i]].num);
    }
}

int main() {
    (void)scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        int h, w, t;
        (void)scanf("%d %d %d", &w, &h, &t);
        brick[i - 1].num = i;
        brick[i - 1].h = h;
        brick[i - 1].w = w;
        brick[i - 1].t = t;
    }

    InitLIST();
    findANS();

}