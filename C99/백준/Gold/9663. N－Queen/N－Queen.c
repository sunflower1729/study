#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX 15
int N;
int answer = 0;



//visit[][][k]로 생성하여 k개의 queen이 생성될 경우 해당 visit를 체크
//시간초과
// int visit[MAX][MAX][MAX + 1] = {0};
// void print_visit(){
//     for(int k = 0; k < N +  1; k++){
//         for(int i = 0; i < N; i++){
//             for(int j = 0; j < N; j++){
//                     printf("%d", visit[i][j][k]);
//             }
//             printf("\n");
//         }
//         printf("\n");
//     }
//     printf("\n");
// }

// void make_visit(int row, int col, int k){
//     for(int i = 0; i < N; i++){
//         for(int j = 0; j < N; j++){
//             visit[i][j][k] = visit[i][j][k - 1];
//         }
//     }
//     visit_col[col] = 1;
//     // for(int i = 0; i < N; i++){
//     //     visit[i][col][k] = 1;
//     // }
//     for(int i = row, j = col; i < N && j < N; i++, j++){
//         visit[i][j][k] = 1;
//     }
//     for(int i = row, j = col; i < N && j >= 0; i++, j--){
//         visit[i][j][k] = 1;
//     }
//     return;
// }

int visit_col[MAX];
int expend_col[2][MAX][MAX + 1] = {0};

void print_expend_col(int k){
    for(int i = 0; i < k; i++){
        for(int j = 0; j < N; j++){
            printf("%d ", expend_col[0][j][i]);
        }
        printf("\n");
    }
    printf("\n");
    for(int i = 0; i < k; i++){
        for(int j = 0; j < N; j++){
            printf("%d ", expend_col[1][j][i]);
        }
        printf("\n");
    }
    printf("\n");
    printf("\n");
}


void make_visit2(int col, int k){
    for(int j = 0; j < N; j++){
        if(j + 1 < N){
            if(expend_col[0][j][k - 1] == 1){ // 우
                expend_col[0][j + 1][k] = 1;
            }
            else{
                expend_col[0][j + 1][k] = 0;
            }
        }
        if(j - 1 >= 0){
            if(expend_col[1][j][k - 1] == -1){
                expend_col[1][j - 1][k] = -1;
            }
            else{
                expend_col[1][j - 1][k] = 0;
            }
        }
    }

    visit_col[col] = 1;
    if(col + 1 < N) expend_col[0][col+1][k] = 1;
    if(col - 1 >= 0) expend_col[1][col-1][k] = -1;

    return;
}

void Queen(int k){
    if(k == N + 1){
        answer++;
        return;
    }
    for(int j = 0; j < N; j++){
        //print_expend_col(k);

        if(visit_col[j] == 1) continue;
        if(expend_col[0][j][k-1] == 1 || expend_col[1][j][k-1] == -1) continue;
        //make_visit(i, j, k);
        make_visit2(j, k);
        Queen(k+1);

        visit_col[j] = 0;
    }
    return;
}

int main(){
    (void)scanf(" %d", &N);

    Queen(1);
    printf("%d", answer);
}