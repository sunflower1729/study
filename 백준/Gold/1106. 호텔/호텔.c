#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
int C, N;

typedef struct promotion{
    int cost;
    int coustormer;
}Promotion;

Promotion pro[21];

int bag[1102] = {0};
//DP 구조를 어떻게 짤 것인가 ?

void print_bag(){
    for(int i = C - 11; i < C + 1; i++){
        printf("%d ", bag[i]);
    }
    printf("\n");
}

void find_cost(){
    int min = 2147483647;
    for(int i = 0; i < C + 1; i++){
        if(bag[i] == 0) continue;
        for(int j = 0; j < N; j++){
            bag[i + pro[j].coustormer] = bag[i + pro[j].coustormer] == 0 ? bag[i] + pro[j].cost : 
            bag[i + pro[j].coustormer] < bag[i] + pro[j].cost ? bag[i + pro[j].coustormer] : bag[i] + pro[j].cost;

            if(i + pro[j].coustormer >= C){
                min = min < bag[i + pro[j].coustormer] ? min : bag[i + pro[j].coustormer];
            }
        }
    }
    printf("%d", min - 1);
}


int main(){
    (void)scanf(" %d %d", &C, &N);

    for(int i = 0; i < N; i++){
        (void)scanf(" %d %d", &pro[i].cost, &pro[i].coustormer);
    }
    bag[0] = 1;
    find_cost();
}