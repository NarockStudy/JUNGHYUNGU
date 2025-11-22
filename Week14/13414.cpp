#include <iostream>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

map<string, int> m;              
vector<pair<int, string>> v;         
int k, l;                            

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> k >> l;

    // l개의 신청 로그 입력
    // 같은 사람이 여러 번 신청하면 마지막 신청 시각으로 갱신
    // 즉, map은 자동으로 마지막 기록만 남기게 됨
    for (int i = 0; i < l; i++) {
        string num;
        cin >> num;
        m[num] = i + 1;             // i+1 → '최근 신청했을수록 더 큰 값'
    }

    // map에는 (ID → 마지막 신청 시각) 형태 저장
    // 이제 이를 벡터에 (신청 시각, ID) 조합으로 저장
    for (auto it = m.begin(); it != m.end(); it++) {
        string x = it->first;       // ID
        int y = it->second;         // 마지막 신청 시각
        v.push_back({y, x});
    }

    // 신청 시각 기준 오름차순 정렬
    // → 오래된 신청이 먼저, 최근 신청이 뒤쪽
    sort(v.begin(), v.end());

    // 선발 인원 k명 출력
    // 만약 지원자가 k명보다 적으면 있는 만큼만 출력
    for (int i = 0; i < min(k, int(v.size())); i++)
        cout << v[i].second << "\n";  // ID 출력
}
