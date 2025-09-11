#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>

int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};

bool y_princess[25]; 
int answer = 0;

using namespace std;
string status[5]; // 5x5 보드 상태 입력

// BFS로 선택된 7칸이 서로 연결되어 있고 'Y'가 4명 이상 아닌지 검사
// 조건 만족 시 answer 증가
void bfs() {
    queue<pair<int, int>> q;
    bool visited[5][5] = {};
    int doyeon = 0, cnt = 0;

    // 선택된 7칸 중 하나를 시작점으로 BFS 탐색 시작
    for (int i = 0; i < 25; i++) {
        if (!y_princess[i]) {
            int x = i / 5;
            int y = i % 5;
            visited[x][y] = true;
            q.push({x, y});
            break;  
        }
    }

    while (!q.empty()) {
        auto cur = q.front(); q.pop();
        cnt++;
        if (status[cur.first][cur.second] == 'Y') doyeon++;
        if (doyeon >= 4) return; // 'Y'가 4명 이상이면 불가능

        // 상하좌우로 연결된 칸 탐색
        for (int dir = 0; dir < 4; dir++) {
            int nx = cur.first + dx[dir];
            int ny = cur.second + dy[dir];
            if (nx < 0 || ny < 0 || nx >= 5 || ny >= 5) continue;
            if (visited[nx][ny]) continue;
            if (y_princess[nx * 5 + ny]) continue; // 선택되지 않은 칸은 패스
            visited[nx][ny] = true;
            q.push({nx, ny});
        }
    }

    // 7칸 전부 연결돼 있으면 경우의 수 카운트
    if (cnt == 7) answer++;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    // 5x5 격자 입력 ('S' 또는 'Y')
    for(int i = 0; i< 5; i++) cin >> status[i];

    // 25칸 중 7칸만 선택되도록 초기화
    fill(y_princess + 7, y_princess + 25, true);

    // 모든 조합(25C7)에 대해 BFS 검사
    do {
        bfs();
    } while(next_permutation(y_princess, y_princess+25));

    cout << answer; // 가능한 경우의 수 출력
}
