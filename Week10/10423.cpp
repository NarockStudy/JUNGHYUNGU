#include <bits/stdc++.h>
using namespace std;

int n, m, k;
int p[1005];
vector<tuple<int, int, int>> edges;

int find(int x) {
    if (p[x] == x) return x;
    return p[x] = find(p[x]);
}

bool Union(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return false;
    p[u] = v;
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;

    for (int i = 0; i <= n; i++) p[i] = i;

    // 발전소 있는 도시를 모두 "0번 가상 노드"와 연결
    for (int i = 0; i < k; i++) {
        int v;
        cin >> v;
        Union(0, v); // 발전소는 이미 전력 연결됨
    }

    // 간선 입력 (가중치가 정렬 기준이 되어야 함)
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({w, u, v});
    }

    // 간선 정렬 (가중치 기준 오름차순)
    sort(edges.begin(), edges.end());

    int answer = 0;

    // MST
    for (auto &[w, u, v] : edges) {
        if (Union(u, v)) { 
            answer += w;
        }
    }

    cout << answer;
}
