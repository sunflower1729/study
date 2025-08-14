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
/*
void swap(Brick* b1, Brick* b2){
    Brick temp;
    temp = *b1;
    *b1 = *b2;
    *b2 = temp;
}

void sort_w(){
    for(int i = 0; i < N; i++){
        for(int j = i+1; j < N; j++){
            if(brick[i].w > brick[j].w){
                swap(&brick[i], &brick[j]);
            }
        }
    }
}
*/

int cmp_by_w(const void* a, const void* b) {
    const Brick* b1 = (const Brick*)a;
    const Brick* b2 = (const Brick*)b;
    return b1->w - b2->w; // 오름차순
}
int cmp_by_t(const void* a, const void* b) {
    const Brick* b1 = (const Brick*)a;
    const Brick* b2 = (const Brick*)b;
    return b1->t - b2->t; // 오름차순
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

void print_box() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%4d ", box[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("\n");
}

void findANS() {
    int answer = 0;
    int answer_x = 0;
    int answer_y = 0;
    for (int i = 0; i < N; i++) {
        if (brick[0].t <= tonLIST[i]) {
            box[0][i] = brick[0].h;
            box_top[0][i][box_point[0][i]++] = 0;
        }
    }
    //print_box();

    for (int i = 1; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // 전에거 그대로 가져와
            box[i][j] = box[i - 1][j];

            memcpy(box_top[i][j], box_top[i - 1][j], (box_point[i - 1][j] + 1) * sizeof(int));
            box_point[i][j] = box_point[i - 1][j];

            if (brick[i].t < tonLIST[j]) { // 판때기가 더 커서 넣을 수 있을 때
                //칸이 크니까 맨 위에 있는 박스와 비교후 넣기
                if (box_point[i][j] > 0) {
                    int top_pnt = box_point[i][j] - 1;
                    int top_box = box_top[i][j][top_pnt];
                    if (brick[top_box].t < brick[i].t) {
                        //현재 i의 t이 더 커서 신경 안 써도 될 떄
                        //하나 추가
                        box[i][j] += brick[i].h;
                        box_top[i][j][box_point[i][j]++] = i;
                    }
                    else if (box[i][j] - brick[top_box].h + brick[i].h < box[i][j]) {
                        //기존이 더 클 때
                        //아무것도 안함
                    }
                    else {
                        //추가한게 더 클 때
                        // 여기서 박스를 삭제하는 로직이 수정되어야함
                        int minus_box = brick[top_box].h;

                        while(top_pnt >= 0 && (box[i][j] - minus_box + brick[i].h >= box[i][j])){
                            top_pnt--;
                            top_box = box_top[i][j][top_pnt];
                            if(top_pnt < 0){
                                break;
                            }
                            if(brick[top_box].t < brick[i].t){
                                //이제 신경 안써도 됨
                                break;
                            }
                            else{
                                //더 빼야함
                                minus_box += brick[top_box].h;
                            }
                            
                        }
                        if(box[i][j] + brick[i].h - minus_box >= box[i][j]){
                            box[i][j] = box[i][j] + brick[i].h - minus_box;
                            box_top[i][j][top_pnt + 1] = i;
                            box_point[i][j] = top_pnt + 2;
                        }
                    }
                }
                else { //아무것도 없는거니까 그냥 올리기
                    //이미 올려짐
                    box[i][j] += brick[i].h;
                    box_top[i][j][box_point[i][j]++] = i;
                }
            }
            else if (brick[i].t == tonLIST[j]) {
                // 같을때 새로운 값 올리기
                box[i][j] += brick[i].h;
                box_top[i][j][box_point[i][j]++] = i;
            }
            //무조건 왼쪽보다 크게
            if(j > 1 && box[i][j] < box[i][j-1]){
                box[i][j] = box[i][j-1];
                memcpy(box_top[i][j], box_top[i][j - 1], (box_point[i][j-1] + 1) * sizeof(int));
                box_point[i][j] = box_point[i][j - 1];
            }
            if (answer < box[i][j]) {
                answer = box[i][j];
                answer_x = i;
                answer_y = j;
            }
        }
        //print_box();
    }
    printf("%d\n", box_point[answer_x][answer_y]);
    for(int i = 0; i < box_point[answer_x][answer_y]; i++) {
        printf("%d\n", brick[box_top[answer_x][answer_y][i]].num);
    }
}

int main() {
    (void)scanf("%d", &N);
    for (int i = 1; i <= N; i++) { // 벽돌 입력 받기
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