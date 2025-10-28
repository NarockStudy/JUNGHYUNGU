#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int n;
int t[10005];           
int indeg[10005];       
int dp[10005];          
vector<int> v[10005];   

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        int k;  
        cin >> t[i] >> k;
        for (int j = 0; j < k; j++) {
            int a;
            cin >> a;
            v[a].push_back(i);   // a 작업이 끝나야 i 시작 가능
            indeg[i]++;          // i의 진입 차수 증가
        }
    }

    queue<int> q;

    //진입 차수가 0인 작업부터 시작 (즉, 바로 시작 가능한 작업)
    for (int i = 1; i <= n; i++) {
        if (indeg[i] == 0) {
            q.push(i);
            dp[i] = t[i];  // 바로 시작 가능한 작업은 자기 시간만 필요
        }
    }

    //위상정렬 기반 DP
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        for (int nxt : v[cur]) {
            indeg[nxt]--;
            dp[nxt] = max(dp[nxt], dp[cur] + t[nxt]); // 선행 작업 최대값 반영
            if (indeg[nxt] == 0) q.push(nxt);          // 모든 선행 완료 시 큐에 삽입
        }
    }

    cout << *max_element(dp + 1, dp + n + 1); // 전체 작업 중 가장 오래 걸리는 시간
}
