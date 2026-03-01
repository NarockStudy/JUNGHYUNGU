#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> v;      // 숫자 저장
vector<char> op;    // 연산자 저장

int answer = -1000000000;

// 두 수 계산 함수
int cal(char oper, int x, int y){
    if (oper == '+') return x + y;
    if (oper == '-') return x - y;
    if (oper == '*') return x * y;
    return 0;
}

// DFS
// cur  : 현재 연산자 인덱스
// sum  : 지금까지 계산된 값
void dfs(int cur, int sum){

    // 모든 연산자를 다 사용했으면 종료
    if(cur == op.size()){
        answer = max(answer, sum);
        return;
    }

    // 괄호 없이 현재 연산 진행
    dfs(cur + 1, cal(op[cur], sum, v[cur + 1]));

    // 다음 연산을 괄호로 먼저 계산하는 경우
    if(cur + 1 < op.size()){
        int temp = cal(op[cur + 1], v[cur + 1], v[cur + 2]);
        dfs(cur + 2, cal(op[cur], sum, temp));
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    string s;

    cin >> n;
    cin >> s;

    // 숫자 / 연산자 분리
    for(int i = 0; i < n; i++){
        if(i % 2 == 0) v.push_back(s[i] - '0');
        else op.push_back(s[i]);
    }

    dfs(0, v[0]);

    cout << answer;
}