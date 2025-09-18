#include <iostream>
#include <queue>
#include <tuple>
#include <string>

using namespace std;

int map[1001][1001];
int d[1001][1001][11][2];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int n, m, k;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        string row;
        cin >> row;
        for (int j = 0; j < m; j++) {
            map[i][j] = row[j] - '0';
        }
    }

    // {y, x, 부순 벽의 수, 현재 시간(낮/밤)} 상태를 저장
    queue<tuple<int, int, int, int>> q;

    // 시작점 (0,0)은 벽을 0개 부순 상태, 낮(0)에서 시작하며 거리는 1
    d[0][0][0][0] = 1;
    q.push({0, 0, 0, 0});

    while (!q.empty()) {
        int y, x, count, time;
        tie(y, x, count, time) = q.front();
        q.pop();

        // 목적지에 도착한 경우, 현재 거리를 출력하고 즉시 종료 
        if (y == n - 1 && x == m - 1) {
            cout << d[y][x][count][time];
            return 0;
        }

        int next_time = 1 - time; // 다음 턴의 시간 (낮->밤, 밤->낮)

        // 이동하지 않고 현재 위치에서 시간을 보내는 경우를 처리
        // 이 선택지는 항상 가능하므로, 4방향 이동보다 먼저 큐에 추가
        if (d[y][x][count][next_time] == 0) {
            d[y][x][count][next_time] = d[y][x][count][time] + 1;
            q.push({y, x, count, next_time});
        }

        // --- 핵심 로직 2: 4방향으로 이동 ---
        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];

            if (ny < 0 || ny >= n || nx < 0 || nx >= m) continue;

            // Case A: 다음 칸이 길(0)인 경우
            if (map[ny][nx] == 0 && d[ny][nx][count][next_time] == 0) {
                d[ny][nx][count][next_time] = d[y][x][count][time] + 1;
                q.push({ny, nx, count, next_time});
            }

            // Case B: 다음 칸이 벽(1)인 경우 (낮에만 부수기 가능)
            if (map[ny][nx] == 1 && time == 0 && count < k && d[ny][nx][count + 1][next_time] == 0) {
                d[ny][nx][count + 1][next_time] = d[y][x][count][time] + 1;
                q.push({ny, nx, count + 1, next_time});
            }
        }
    }

    // 큐가 비워질 때까지 목적지에 도달하지 못한 경우
    cout << -1;
    return 0;
}