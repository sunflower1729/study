#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAXN 32000
#define MAXM 100000

int N, M;

typedef struct queue{
    int n;
}Queue;

Queue q[MAXM];
int front = 0, rear = -1;

void push(int num){
    q[++rear].n = num;
}

int pop(){
    return q[front++].n;
}

int to_Node[MAXM + 1] = {0}; // 초기화 1, 에러 방지
int next[MAXM + 1] = {0};
int head[MAXN + 1] = {0};

int have_v[MAXN + 1] = {0};

void add_v(int from, int to, int i){
    to_Node[i] = to;
    next[i] = head[from];
    head[from] = i;
}

void find_zero_v(){
    for(int i = 1; i <= N; i++){
        if(have_v[i] == 0) push(i);
    }
}

void sort_k(){
    while(front <= rear){
        int num = pop();
        printf("%d ", num);
        while(head[num] != -1){
            int pnt = to_Node[head[num]];
            have_v[pnt]--;
            if(have_v[pnt] == 0) push(pnt);
            head[num] = next[head[num]];
        }
    }
}

int main(){
    
    (void)scanf("%d %d", &N, &M);

    for(int i = 0; i <= N; i++){
        head[i] = -1;
    }

    for(int i = 1; i <= M; i++){
        int a, b;
        (void)scanf("%d %d", &a, &b);
        add_v(a, b, i);
        have_v[b]++;
    }
    find_zero_v();
    sort_k();
}