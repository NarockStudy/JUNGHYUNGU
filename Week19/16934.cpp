#include <bits/stdc++.h>
using namespace std;

unordered_map<string, int> cnt;
unordered_set<string> usedPrefix;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    cin >> n;

    // n번 입력을 처리하며 매 입력마다 결과를 출력
    for (string s; n--; cout << '\n') {
        cin >> s;

        cnt[s]++;              
        bool printed = false;  

        string t;
        // s의 모든 접두사 생성: s[0..0], s[0..1], ... s[0..len-1]
        for (int i = 0; i < (int)s.size(); i++) {
            t = s.substr(0, i + 1);

            // 아직 출력 안 했고, 이 접두사가 처음 등장이라면 그걸 출력 (가장 짧은 유일 접두사)
            if (!printed && !usedPrefix.count(t)) {
                cout << t;
                printed = true;
            }

            // 접두사는 무조건 집합에 등록 (다음 사람에게는 "이미 나온 접두사"가 됨)
            usedPrefix.insert(t);
        }

        // 모든 접두사가 이미 사용된 경우 (printed == false)
        if (!printed) {
            // 처음 나온 닉네임이면 그대로 출력
            if (cnt[s] == 1) {
                cout << s;
            }
            // 중복 닉네임이면 닉네임 + 등장횟수 출력
            else {
                cout << s << cnt[s];
            }
        }
    }
}
