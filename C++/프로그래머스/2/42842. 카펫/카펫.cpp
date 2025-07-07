#include <string>
#include <vector>
#include <iostream>
using namespace std;



vector<int> solution(int brown, int yellow) {
    vector<int> answer;
    int x = brown + yellow;
    for(int w = 3; w < x; w++){
        if(!(x%w == 0)) continue;
        int h = x / w;
        if(((h+w)*2 - 4) == brown){
            if(h >= w){
                answer.push_back(h);
                answer.push_back(w);
           }
           else{
                answer.push_back(w);
                answer.push_back(h);
           }
            break;
        }
    }
    
    return answer;
}

// B + Y = X 라 했을 때
// A * B ~ B * A까지 검사한다.
// (단, A >= 3)
// A * B 의 테두리 값이 A가 나올경우 검사 종료
// 길이가 긴 것부터 출력한다.