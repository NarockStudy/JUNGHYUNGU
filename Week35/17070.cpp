#include <iostream>
using namespace std;

int board[17][17];
int n;
int answer = 0;

void dfs(int x, int y, int dir) {
    if (x == n && y == n) {
        answer++;
        return;
    }

    // 1. 현재 방향이 가로(0) 또는 대각선(1)일 때
    //    -> 오른쪽(가로) 이동 
    if (dir == 0 || dir == 1) {
        int nx = x;
        int ny = y + 1;

        // 오른쪽 칸이 범위 안이고 빈칸이어야 이동 
        if (ny <= n && board[nx][ny] == 0) {
            dfs(nx, ny, 0);
        }
    }

    // 2. 현재 방향이 세로(2) 또는 대각선(1)일 때
    //    -> 아래쪽(세로) 이동 
    if (dir == 1 || dir == 2) {
        int nx = x + 1;
        int ny = y;

        // 아래 칸이 범위 안이고 빈칸이어야 이동 가능
        if (nx <= n && board[nx][ny] == 0) {
            dfs(nx, ny, 2);
        }
    }

    // 3. 모든 방향에서 대각선 이동 검토 가능
    //    단, 오른쪽 / 아래 / 오른쪽아래 3칸이 모두 비어 있어야 함
    {
        int nx = x + 1;
        int ny = y + 1;

        if (nx <= n && ny <= n &&
            board[x][y + 1] == 0 &&
            board[x + 1][y] == 0 &&
            board[nx][ny] == 0) {
            dfs(nx, ny, 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> board[i][j];
        }
    }

    // 시작 파이프: (1,1) ~ (1,2)
    // 끝점 기준으로 보면 (1,2), 방향은 가로(0)
    dfs(1, 2, 0);

    cout << answer;
    return 0;
}