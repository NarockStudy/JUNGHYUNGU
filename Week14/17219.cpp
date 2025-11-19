#include <iostream>
#include <map>

using namespace std;

int n, m;
string a, b;
map<string, string> mp; 

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    // 예: a = "apple", b = "사과" 라면 mp["apple"] = "사과"
    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        mp[a] = b;
    }

    // m개의 질의를 받아 mp에서 해당 키의 value 출력
    for (int i = 0; i < m; i++) {
        cin >> a;           // 찾을 문자열 입력
        cout << mp[a] << "\n"; // 매핑된 결과 출력
    }
}
