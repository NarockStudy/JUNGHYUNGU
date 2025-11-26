#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define X first
#define Y second

int board[50][50];
int visited[50][50];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

int n, l, r;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> l >> r;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> board[i][j];

    int answer = 0;

    while (true) {
        // 방문 배열 초기화
        fill(&visited[0][0], &visited[0][0] + 50 * 50, 0);

        vector<vector<pair<int,int>>> unions;  // 인구 이동이 일어나야 하는 연합들 저장

        // 모든 칸에서 BFS 수행
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {

                if (visited[i][j]) continue;

                vector<pair<int,int>> group;
                queue<pair<int,int>> q;

                visited[i][j] = 1;
                q.push({i, j});
                group.push_back({i, j});

                // 연합 찾기 BFS
                while (!q.empty()) {
                    auto cur = q.front(); q.pop();

                    for (int dir = 0; dir < 4; dir++) {
                        int nx = cur.X + dx[dir];
                        int ny = cur.Y + dy[dir];
                        if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
                        if (visited[nx][ny]) continue;

                        int diff = abs(board[nx][ny] - board[cur.X][cur.Y]);
                        // L ≤ diff ≤ R 범위만 이동 가능
                        if (diff < l || diff > r) continue;

                        visited[nx][ny] = 1;
                        q.push({nx, ny});
                        group.push_back({nx, ny});
                    }
                }

                if (group.size() > 1) unions.push_back(group);
            }
        }

        // 더 이상 이동할 연합 없음 → 종료
        if (unions.empty()) break;

        // 인구 이동 수행
        answer++;

        for (auto &group : unions) {
            int sum = 0;
            for (auto &cell : group)
                sum += board[cell.X][cell.Y];

            int new_pop = sum / group.size();

            for (auto &cell : group)
                board[cell.X][cell.Y] = new_pop;
        }
    }

    cout << answer;
}
