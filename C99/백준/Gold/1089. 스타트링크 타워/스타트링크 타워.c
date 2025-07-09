#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int n;
int lamp[5][3][9] = {0};
int lamp_num[9][10] = {0};
int num[10][5][3] = {
{
    {1, 1, 1},
    {1, 0, 1},
    {1, 0, 1},
    {1, 0, 1},
    {1, 1, 1}
}, {
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1}
}, {
    {1, 1, 1},
    {0, 0, 1},
    {1, 1, 1},
    {1, 0, 0},
    {1, 1, 1}
}, {
    {1, 1, 1},
    {0, 0, 1},
    {1, 1, 1},
    {0, 0, 1},
    {1, 1, 1}
}, {
    {1, 0, 1},
    {1, 0, 1},
    {1, 1, 1},
    {0, 0, 1},
    {0, 0, 1}
}, {
    {1, 1, 1},
    {1, 0, 0},
    {1, 1, 1},
    {0, 0, 1},
    {1, 1, 1}
}, {
    {1, 1, 1},
    {1, 0, 0},
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1}
}, {
    {1, 1, 1},
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1}
}, {
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1}
}, {
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1},
    {0, 0, 1},
    {1, 1, 1}
}
};

void print_lamp(){
    for(int j = 0; j < 5; j ++){
        for(int i = 0; i < n; i++){
            for(int k = 0; k < 3; k++){
                printf("%d ", lamp[j][k][i]);
            }
        }
        printf("\n");
    }
}


int check_num(int idx){
    if(lamp[1][1][idx] == 1 || lamp[3][1][idx] == 1){
        return -1;
    }
    
    int flag = 0;
    for(int k = 0; k < 10; k++){
        for(int j = 0; j < 5 && flag == 0; j++){
            for(int i = 0; i < 3; i++){
                if(num[k][j][i] == 0 && lamp[j][i][idx] == 1){
                    flag = 1; 
                    break;
                }
            }
        }
        if(flag){
            flag = 0;
        }
        else{
            //printf("%d번쨰는 %d가능함\n", idx, k);
            lamp_num[idx][k] = 1;
        }
    }
    
    return 0;
}

double exponent = 0;
int cnt = 0;

//재귀함수 -> SIGTERM
void make_num(int a, double b){ // a는 몇번째인지, b는 해당 수가 뭔지
    if(a == n){
        exponent += b;
        cnt++;
        printf("%f\n", exponent);
        return;
    }
    for(int i = 0; i < 10; i++){
        if(lamp_num[a][i] == 1){
            if(a == 0){
                make_num(a+1, i);
            }
            else{
                make_num(a+1, b*10 + i);
            }
        }
    }
}

//많은 스택 -> 스택 자리 부족, 스택의 크기를 키우면 -> 메모리초과
void make_num_iterative() {
    // 스택 구조 정의
    typedef struct {
        int pos;      // 자리 위치 (a)
        double value; // 지금까지 만든 수 (b)
    } StackFrame;

    StackFrame stack[10000];  // 적당히 큰 크기
    int top = 0;

    // 초기 스택에는 첫 자릿수에서 가능한 숫자들만 넣음
    for (int i = 0; i < 10; i++) {
        if (lamp_num[0][i] == 1) {
            stack[top++] = (StackFrame){1, (double)i};
        }
    }

    while (top > 0) {
        StackFrame curr = stack[--top];

        if (curr.pos == n) {
            exponent += curr.value;
            cnt++;
            continue;
        }

        for (int i = 0; i < 10; i++) {
            if (lamp_num[curr.pos][i] == 1) {
                stack[top++] = (StackFrame){curr.pos + 1, curr.value * 10 + i};
            }
        }
    }
}

double answer = 0;

int check(){
    int flag2 = 0;
    for(int i = 0; i < n; i++){
        flag2 = check_num(i);
        if(flag2 == -1)
            return -1;
    }
    
    for(int i = 0; i < n; i++){
        double temp = 0;
        cnt = 0;
        for(int k = 0; k < 10; k++){
            if(lamp_num[i][k] == 1){
                temp += k;
                cnt++;
            }
        }
        if(i == 0){
            answer = (temp / cnt);
        }
        else{
            answer = answer * 10;
            answer += (temp / cnt);
        }
        
    }

    return 1;
}

int main(){
    (void)scanf("%d ", &n);

    char c;

    for(int j = 0; j < 5; j ++){
        for(int i = 0; i < n; i++){
            for(int k = 0; k < 3; k++){
                c = getchar();
                if(c == '#')
                    lamp[j][k][i] = 1;
                else
                    lamp[j][k][i] = 0;
            }
            c = getchar();
        }
    }
        
    int flag2 = check();
    if(flag2 == 1){
        printf("%f", answer);
    }
    else{
        printf("-1");
    }
}