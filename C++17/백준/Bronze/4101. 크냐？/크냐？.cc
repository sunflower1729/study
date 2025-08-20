#include <iostream>
using namespace std;
int main(){
    int a, b;
    cin >> a >> b;
    while(!(a == 0 && b== 0)) {   
        if(a > b){
            cout << "Yes" << endl;
        }
        else{
            cout << "No" << endl;
        }
        cin >> a >> b;
    }

}