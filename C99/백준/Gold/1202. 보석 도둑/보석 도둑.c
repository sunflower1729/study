#define _CRT_NO_SECURE_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#define MAX 300000
#define MAXW 100000000

typedef struct jewelry{
    int M;
    int V;
}Jewelry;

typedef struct queue{
    int V;
}queue;

queue preq[MAX + 1] = {0};

int rear = 0;

void swap(queue* a, queue* b){
    queue temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void push(int v){
    preq[++rear].V = v;
    int child = rear;
    int parent = rear / 2;
    while(parent >= 1 && preq[parent].V < preq[child].V){
        swap(&preq[parent], &preq[child]);
        child = parent;
        parent = child / 2;
    }
}

int pop(){
    int temp = preq[1].V;
    preq[1].V = preq[rear--].V;
    int parent = 1;
    while(1){
        int left = parent * 2;
        int right = parent * 2 + 1;
        int max_index = parent;
        
        if (left <= rear && preq[left].V > preq[max_index].V) {
            max_index = left;
        }
        if (right <= rear && preq[right].V > preq[max_index].V) {
            max_index = right;
        }

        if (max_index == parent) break;

        swap(&preq[parent], &preq[max_index]);
        parent = max_index;
    }

    return temp;
}

int N, K;
Jewelry jewelry[MAX] = {0};
int input_bag[MAX] = {0};


int compareJ(const void* a, const void* b){
    const Jewelry *ja = (const Jewelry *)a;
    const Jewelry *jb = (const Jewelry *)b;
    return ja->M - jb->M;
}

int compareB(const void* a, const void* b){
    return *(int*)a - *(int*)b;
}

void printf_j(){
    for(int i = 0; i < N; i++){
        printf("%d ", jewelry[i].V);
    }
    printf("\n");
}

void printf_q(){
    printf("q\n");
    for(int i = 0; i < rear + 1; i++){
        printf("%d ", preq[i].V);
    }
    printf("\n");
}

void INIT_BAG(){
    long long answer = 0;
    int j = 0;
    for(int i = 0; i < K; i++){
        while(j < N && jewelry[j].M <= input_bag[i]){
            push(jewelry[j].V);
            j++;
        }
        if(rear > 0){
            answer += pop();
        }
    }
    printf("%lld", answer);
}


int main(){
    (void)scanf(" %d %d", &N, &K);
    for(int i = 0; i < N; i++){
        int m, v;
        (void)scanf(" %d %d", &m, &v);
        jewelry[i].M = m;
        jewelry[i].V = v;
    }
    for(int i = 0; i < K; i++){
        int c;
        (void)scanf(" %d", &c);
        input_bag[i] = c;
    }

    qsort(jewelry, N, sizeof(Jewelry), compareJ);
    qsort(input_bag, K, sizeof(int), compareB);
    INIT_BAG();
}