#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, q;
vector<int> efficiency;
vector<int> m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q;

    efficiency.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> efficiency[i];
    }

    m.resize(q);
    for (int i = 0; i < q; i++) {
        cin >> m[i];
    }

    // 연비를 오름차순으로 정렬
    sort(efficiency.begin(), efficiency.end());

    for (int i = 0; i < q; i++) {
        // 중앙값 m[i] 이상인 첫 번째 위치 탐색
        int idx = lower_bound(efficiency.begin(), efficiency.end(), m[i]) - efficiency.begin();

        // 중앙값이 배열에 존재하지 않으면 0 출력
        if (idx == n || efficiency[idx] != m[i]) cout << 0 << '\n'; 
        
        // 중앙값보다 작은 자동차 수 × 큰 자동차 수
        else cout << 1LL * idx * (n - idx - 1) << '\n';
    }

    return 0;
}
