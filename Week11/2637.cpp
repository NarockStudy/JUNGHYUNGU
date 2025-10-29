#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int n, m;
int indeg[105];
int dp[105][105];
int check[105];
vector<pair<int, int>> adj[103];
queue<int> q;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
     
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y, k;
        cin >> x >> y >> k;
        adj[y].push_back({x, k}); // y를 조립하면 x가 만들어짐 (y → x)
        indeg[x]++;               // x의 진입차수 증가
    }

    // 진입차수가 0인 기본 부품 초기화
    for (int i = 1; i <= n; i++) {
        if (indeg[i] == 0) {
            check[i] = 1;         // 기본 부품 표시
            q.push(i);            // 큐에 삽입
            dp[i][i] = 1;         // 자기 자신 1개 필요
        }
    }

    // 위상정렬을 이용한 부품 조합 계산
    while (!q.empty()) {
        int cur = q.front(); q.pop();

        for (auto a : adj[cur]) {
            indeg[a.first]--;
            if (indeg[a.first] == 0) q.push(a.first);

            //  하위 부품(cur)의 조합을 상위 부품(a.first)에 누적
            // cur 부품이 a.second개 필요하므로, 각 기본 부품의 개수 * a.second
            for (int j = 1; j <= n; j++)
                dp[a.first][j] += dp[cur][j] * a.second;
        }
    }

    //  완제품(n)을 구성하는 기본 부품만 출력
    for (int i = 1; i <= n; i++) {
        if (check[i]) cout << i << " " << dp[n][i] << "\n";
    }
}
