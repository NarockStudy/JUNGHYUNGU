
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int N;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;

    vector<vector<int>> board(N, vector<int>(N));
    deque<tuple<int, int, int, int>> dq;

    vector<vector<array<int, 4>>> dist(N, vector<array<int, 4>>(N));

    for (int i = 0; i < N; i++) 
        for (int j = 0; j < N; j++) cin >> board[i][j];

    for (int i = 0; i < N; i++)  
        for (int j = 0; j < N; j++) dist[i][j].fill(INF);

    // 시작점: (2,2) -> 0-based (1,1)
    for (int d = 0; d < 4; d++) {
        dist[1][1][d] = 0;
        dq.push_back({1, 1, d, 0});
    }

    while (!dq.empty()) {
        auto [x, y, dir, cost] = dq.front();
        dq.pop_front();

        if (cost != dist[x][y][dir]) continue;

        if (x == N - 2 && y == N - 2) {
            cout << cost << '\n';
            return 0;
        }

        int nx = x + dx[dir];
        int ny = y + dy[dir];

        if (board[nx][ny] == 0) {
            // 앞이 빈 칸이면 반드시 직진 (비용 1)
            if (dist[nx][ny][dir] > cost + 1) {
                dist[nx][ny][dir] = cost + 1;
                dq.push_back({nx, ny, dir, cost + 1});
            }
        } else {
            // 앞이 벽이면 방향 전환 가능 (비용 0)
            for (int nd = 0; nd < 4; nd++) {
                if (nd == dir) continue;
                if (dist[x][y][nd] > cost) {
                    dist[x][y][nd] = cost;
                    dq.push_front({x, y, nd, cost});
                }
            }
        }
    }

    cout << -1 << '\n';
    return 0;
}
