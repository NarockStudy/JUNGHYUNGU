#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <climits>

using namespace std;

#define X first
#define Y second

int w, h;
char board[20][20];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

// start에서 모든 칸까지의 최단거리 계산
vector<vector<int>> bfs(pair<int, int> start) {
    vector<vector<int>> dist(h, vector<int>(w, -1));
    queue<pair<int, int>> q;

    q.push(start);
    dist[start.X][start.Y] = 0;

    while (!q.empty()) {
        auto cur = q.front();
        q.pop();

        for (int dir = 0; dir < 4; dir++) {
            int nx = cur.X + dx[dir];
            int ny = cur.Y + dy[dir];

            if (nx < 0 || ny < 0 || nx >= h || ny >= w) continue;
            if (board[nx][ny] == 'x') continue;
            if (dist[nx][ny] != -1) continue;

            dist[nx][ny] = dist[cur.X][cur.Y] + 1;
            q.push({nx, ny});
        }
    }

    return dist;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while (true) {
        cin >> w >> h;
        if (w == 0 && h == 0) break;

        vector<pair<int, int>> points;
        pair<int, int> robot;
        vector<pair<int, int>> dirty;

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                cin >> board[i][j];

                if (board[i][j] == 'o') {
                    robot = {i, j};
                } else if (board[i][j] == '*') {
                    dirty.push_back({i, j});
                }
            }
        }

        // points[0] = 로봇 위치, points[1..] = 더러운 칸들
        points.push_back(robot);
        for (auto p : dirty) {
            points.push_back(p);
        }

        int n = points.size();

        // dist[i][j] = points[i]에서 points[j]까지의 최단거리
        vector<vector<int>> dist(n, vector<int>(n, -1));

        bool impossible = false;

        for (int i = 0; i < n; i++) {
            auto d = bfs(points[i]);

            for (int j = 0; j < n; j++) {
                dist[i][j] = d[points[j].X][points[j].Y];

                // 어떤 더러운 칸에 도달할 수 없으면 답은 -1
                if (dist[i][j] == -1) {
                    impossible = true;
                }
            }
        }

        if (impossible) {
            cout << -1 << "\n";
            continue;
        }

        // 더러운 칸 방문 순서
        vector<int> order;
        for (int i = 1; i < n; i++) {
            order.push_back(i);
        }

        int answer = INT_MAX;

        do {
            int total = 0;
            int cur = 0; // 시작은 로봇 위치

            for (int next : order) {
                total += dist[cur][next];
                cur = next;
            }

            answer = min(answer, total);

        } while (next_permutation(order.begin(), order.end()));

        cout << answer << "\n";
    }

    return 0;
}