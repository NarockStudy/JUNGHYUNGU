#include <bits/stdc++.h>
using namespace std;

int n, m;
int p[1005];
double answer = 0;

vector<pair<int, int>> v1;
vector<tuple<double, int, int>> v2;

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

double dist(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) p[i] = i;

    v1.push_back({0, 0}); 

    // 각 우주신 좌표 입력
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        v1.push_back({x, y});
    }

    // 이미 연결된 통로 정보 입력
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        Union(a, b); // 이미 연결된 경우 미리 병합
    }

    // 모든 우주신 간 거리 계산
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            double d = dist(v1[i].first, v1[i].second, v1[j].first, v1[j].second);
            v2.push_back({d, i, j});
        }
    }

    sort(v2.begin(), v2.end());

    // 크루스칼 알고리즘으로 MST 구성
    for (auto &[d, u, v] : v2)
        if (Union(u, v)) answer += d;

    cout << fixed << setprecision(2) << answer;
}
