#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

int n, k;
set<string> s;  

int main(){
    cin >> n;

    for(int i = 0 ; i < n ; i++){
        cin >> k;
        string temp = "", st = "";

        // 한 개미의 경로를 순서대로 누적
        for(int j = 0 ; j < k ; j++){
            cin >> temp;

            // 구분자 '*'를 붙여 계층 구조 표현
            st += "*" + temp;

            // 중간 경로까지 모두 저장
            s.insert(st);
        }
    }

    // 위에서부터 출력하면 계층 순서 유지
    for(auto a : s){
        // 깊이 = '*' 개수 - 1
        int depth = count(a.begin(), a.end(), '*') - 1;

        // 현재 단계의 이름만 추출
        int pos = a.find_last_of('*');
        string name = a.substr(pos + 1);

        // 깊이만큼 "--" 출력
        for(int i = 0 ; i < depth; i++) cout << "--";

        cout << name << "\n";
    }
}
