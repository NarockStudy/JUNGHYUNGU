#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

string s;
int n;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> s;
    n = s.length();
    vector<string> v(n);
    // 문자열의 i번째 위치부터 끝까지 자른 접미사 생성
    for(int i = 0; i < n; i++) v[i] = s.substr(i, n);
        
    // 모든 접미사를 사전순으로 정렬
    sort(v.begin(), v.end());
    // 정렬된 접미사 출력
    for(int i = 0; i < n; i++) cout << v[i] << "\n";
        
    return 0;
}