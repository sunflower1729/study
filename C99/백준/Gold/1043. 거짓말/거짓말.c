#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct person{
    int party_cnt;
    int party[50];
}Person;

//사람은 0번 없으므로 1번부터 시작
Person person[51] = {0};
int party[51] = {0};
int member[51][51] = {0}; // i번쨰 파티 멤버들

int N, M;
int trueman[51] = {0}; //1이면 진실아는사람 0이면 몰라

int check_person(int p){
    if(trueman[p] == 1){
        return 1;
    }
    return 0;
}

int s[50];
int s_point = -1;

void push(int a){
    s[++s_point] = a;
}

int pop(){
    return s[s_point--];
}

void check_party(){
    while(s_point >= 0){
        int mem = pop();
        for(int i = 0; i < person[mem].party_cnt; i++){
            int newparty = person[mem].party[i];
            party[newparty] = 1;
            for(int j = 0; member[newparty][j] != 0; j++){
                if(trueman[member[newparty][j]]) continue;
                trueman[member[newparty][j]] = 1;
                push(member[newparty][j]);
            }
        }
    }
}

void change_party_true(){
    int flag = 0;
    for(int i = 0; i < M; i++){
        for(int j = 0; member[i][j] != 0; j++){
            int mem = member[i][j];
            if(trueman[mem]){
                flag = 1;
                break;
            }
        }
        if(flag){
            party[i] = 1;
            for(int j = 0; member[i][j] != 0; j++){
                int mem = member[i][j];
                if(trueman[mem]) continue;
                trueman[mem] = 1;
                push(mem);
            }
            flag = 0;
        }
        else{ //이떄만 추가해줘
            for(int j = 0; member[i][j] != 0; j++){
                int mem = member[i][j];
                person[mem].party[person[mem].party_cnt++] = i; //해당 인원이 가는 파티 추가
            }            
        }
        if(s_point >= 0) {
            check_party();
        }
    }
}


int find_answer(){
    int answer = 0;
    for(int i = 0; i < M; i++){
        if(party[i] == 1) answer++;
    }
    printf("%d", M-answer);
}

int main(){
    int answer = 0;
    (void)scanf(" %d %d", &N, &M);
    
    int true_num;
    (void)scanf(" %d", &true_num);
    for(int i = 0; i < true_num; i++){
        int man;
        (void)scanf(" %d", &man);
        trueman[man] = 1;
    }
    if(true_num == 0){
        printf("%d", M);
        return 0;
    }

    for(int i = 0; i < M; i++){ //파티번호
        //파티 인원수
        int flag = 0;
        int party_num;
        (void)scanf(" %d", &party_num); 

        for(int j = 0; j < party_num; j++){
            (void)scanf(" %d", &member[i][j]);
        }
    }

    change_party_true();
    find_answer();

}