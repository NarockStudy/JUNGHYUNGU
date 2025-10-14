#include <iostream>
using namespace std;

int p[100001];

int find(int a) {
    if (a == p[a]) return a;
    return p[a] = find(p[a]);
}

void Union(int a, int b) {
    a = find(a);
    b = find(b);
    if (a > b) swap(a, b);
    p[b] = a;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m, answer = 0;
    cin >> n >> m;
    for (int i = 0; i <= n; i++) p[i] = i; // 0..n 초기화

    while (m--) {
        int g;
        cin >> g;          
        g = find(g);
        if (g == 0) break; // 더 이상 도킹 불가
        Union(g, g - 1);   // g를 사용했으니 g-1로 연결
        answer++;
    }

    cout << answer;
    return 0;
}
