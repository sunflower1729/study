#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAXN 100001
#define MAXM 700000

int N, M;

typedef struct node {
    int to;
    int value;
    struct node* next;
}Node;

typedef Node* pNode;

pNode head[MAXN] = { 0 };


void addNODE(int from, int to, int value) {
    pNode temp = (pNode)malloc(sizeof(Node));
    if (temp == NULL) {
        printf("malloc error");
        exit(1);
    }
    temp->to = to;
    temp->value = value;
    temp->next = head[from];
    head[from] = temp;
}

typedef struct q {
    int to;
    long long value;
}Queue;

Queue pre_q[5000000] = { 0 };
int q_pnt = 0;

void swap_q(Queue* a, Queue* b) {
    Queue temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void push(int t, long long v) {
    Queue temp = (Queue){ t, v };
    pre_q[++q_pnt] = temp;
    int child = q_pnt;
    int parent = q_pnt / 2;

    while (parent >= 1 && pre_q[child].value < pre_q[parent].value) {
        swap_q(&pre_q[child], &pre_q[parent]);
        child = parent;
        parent = child / 2;
    }
}

Queue pop() {
    Queue temp = pre_q[1];
    pre_q[1] = pre_q[q_pnt--];

    int parent = 1;
    int min = parent;
    while (1) {
        int left = parent * 2;
        int right = parent * 2 + 1;
        if (left <= q_pnt && pre_q[min].value > pre_q[left].value) {
            min = left;
        }
        if (right <= q_pnt && pre_q[min].value > pre_q[right].value) {
            min = right;
        }
        if (min == parent) {
            break;
        }
        swap_q(&pre_q[parent], &pre_q[min]);
        parent = min;
    }

    return temp;
}

long long map[MAXN] = { 0 };

void find_route() {
    for (int i = 1; i <= N; i++) map[i] = 1e18;
    map[1] = 0;
    push(1, 0);

    while (q_pnt >= 1) {
        Queue go = pop();
        int to = go.to;
        long long value = go.value;
        if (value > map[to]) continue;
        if (to == N) break; 

        pNode temp = head[to];
        while (temp != NULL) {
            long long new_value;
            if (temp->value < value % M) {
                new_value = ((value / M) + 1) * M + temp->value;
            }
            else {
                new_value = ((value / M) * M) + temp->value;
            }
            new_value++;

            if(new_value < map[temp->to]){
                map[temp->to] = new_value;
                push(temp->to, new_value);
            }
            temp = temp->next;
        }
    }

    printf("%lld", map[N]);
}

int main() {
    (void)scanf("%d %d", &N, &M);
    for (int i = 0; i < M; i++) {
        int f, t;
        (void)scanf("%d %d", &f, &t);
        addNODE(f, t, i);
        addNODE(t, f, i);
    }
    find_route();
}
