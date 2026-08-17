#include <iostream>
#include <vector>
using namespace std;

int n, m;

int main() {
    ios::sync_with_stdio(p);
    cin.tie(0);
    cin >> n >> m;

    vector<vector<long long>> a(n, vector<long long>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    // → ↗ ↑ ↖ ← ↙ ↓ ↘
    int dr[8] = {0, -1, -1, -1, 0, 1, 1, 1};
    int dc[8] = {1, 1, 0, -1, -1, -1, 0, 1};

    vector<pair<int, int>> nutrient = {
        {n - 1, 0},
        {n - 1, 1},
        {n - 2, 0},
        {n - 2, 1}
    };

    while (m--) {
        int d, p;
        cin >> d >> p;
        d--;

        vector<pair<int, int>> moved;
        vector<vector<bool>> used(n, vector<bool>(n, false));

        // 1. 영양제 이동
        for (auto [r, c] : nutrient) {
            int nr = (r + dr[d] * (p % n) + n) % n;
            int nc = (c + dc[d] * (p % n) + n) % n;

            moved.push_back({nr, nc});
            used[nr][nc] = true;
        }

        // 2. 영양제 투입
        for (auto [r, c] : moved) {
            a[r][c]++;
        }

        // 3. 대각선 나무 개수만큼 성장
        int rr[4] = {-1, -1, 1, 1};
        int cc[4] = {-1, 1, -1, 1};

        for (auto [r, c] : moved) {
            int cnt = 0;

            for (int k = 0; k < 4; k++) {
                int nr = r + rr[k];
                int nc = c + cc[k];

                if (nr >= 0 && nr < n &&
                    nc >= 0 && nc < n &&
                    a[nr][nc] >= 1) {
                    cnt++;
                }
            }

            a[r][c] += cnt;
        }

        // 4. 새로운 영양제 생성
        nutrient.clear();

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (!used[r][c] && a[r][c] >= 2) {
                    a[r][c] -= 2;
                    nutrient.push_back({r, c});
                }
            }
        }
    }

    long long answer = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            answer += a[i][j];
        }
    }

    cout << answer << '\n';

    return 0;
}