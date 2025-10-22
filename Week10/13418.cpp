#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

vector<int> p(1005, -1);
int n, m;

int find(int x) {
    if (p[x] < 0) return x;
    return p[x] = find(p[x]);
}

bool Union(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return false;
    p[u] = v;
    return true;
}

int mst(vector<tuple<int,int,int>> &edges) {
    fill(p.begin(), p.end(), -1);
    int uphill = 0, cnt = 0;

    for (auto &[c, u, v] : edges) {
        if (!Union(u, v)) continue;
        if (c == 0) uphill++;   // c==0은 내리막 → 피로도 없음, 
                                // c==1은 오르막 → 피로도 있음 
        cnt++;
        if (cnt == n) break; // 간선 n개면 완료
    }
    return uphill * uphill;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    vector<tuple<int,int,int>> edges;

    for (int i = 0; i < m + 1; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        edges.push_back({c, u, v});
    }

    // 오르막 최소 (내리막 우선)
    sort(edges.begin(), edges.end());
    int minFatigue = mst(edges);

    // 오르막 최대 (오르막 우선)
    sort(edges.rbegin(), edges.rend());
    int maxFatigue = mst(edges);

    cout << minFatigue - maxFatigue  ;
}
