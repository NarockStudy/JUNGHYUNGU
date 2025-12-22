#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int t, n;
string s;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> t;

    while(t--){
        cin >> n;

        vector<string> v;
        for(int i = 0; i < n; i++){
            cin >> s;
            v.push_back(s);
        }

        sort(v.begin(), v.end());
        // 사전순 정렬 → 접두어 관계는 인접한 문자열에서만 발생

        bool conflict = false;

        for(int i = 0; i < v.size() - 1; i++){
            // v[i]가 v[i+1]의 접두어인지 확인
            if(v[i] == v[i + 1].substr(0, v[i].length())){
                conflict = true;
                break;
            }
        }

        if(conflict) cout << "NO\n";   // 접두어 충돌 존재
        else cout << "YES\n";          // 일관성 유지
    }
}
