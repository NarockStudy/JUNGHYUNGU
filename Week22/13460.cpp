#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct state {
    int redX, redY, // 빨간 구슬 위치
    blueX, blueY,   // 파란 구슬 위치
    depth;          // 기울인 횟수
};

int n, m;
char board[10][10];

bool visited[10][10][10][10];

queue<state> q;

int dirX[] = {0, 1, 0, -1};
int dirY[] = {1, 0, -1, 0};

void roll(int& x, int& y, int& moveCnt, int dir) {
    while (board[x + dirX[dir]][y + dirY[dir]] != '#' &&
           board[x][y] != 'O') {
        x += dirX[dir];
        y += dirY[dir];
        moveCnt++;
    }
}

void bfs() {
    while (!q.empty()) {
        state cur = q.front();
        q.pop();

        // 10번 초과면 실패
        if (cur.depth >= 10) break;

        // 4방향으로 기울이기
        for (int dir = 0; dir < 4; dir++) {
            int next_redX = cur.redX, next_redY = cur.redY,
            next_blueX = cur.blueX, next_blueY = cur.blueY;

            int red_cnt = 0, blue_cnt = 0;
            int next_depth = cur.depth + 1;

            // 빨간/파란 구슬 각각 굴리기
            roll(next_redX, next_redY, red_cnt, dir);
            roll(next_blueX, next_blueY, blue_cnt, dir);

            // 파란 구슬이 구멍에 들어가면 실패 → 무시
            if (board[next_blueX][next_blueY] == 'O') continue;

            // 빨간 구슬만 구멍에 들어가면 성공
            if (board[next_redX][next_redY] == 'O') {
                cout << next_depth;
                return;
            }

            // 두 구슬이 같은 칸에 겹친 경우 처리
            // 더 많이 이동한 구슬을 한 칸 뒤로
            if (next_redX == next_blueX && next_redY == next_blueY) {
                if (red_cnt > blue_cnt) {
                    next_redX -= dirX[dir];
                    next_redY -= dirY[dir];
                } else {
                    next_blueX -= dirX[dir];
                    next_blueY -= dirY[dir];
                }
            }

            // 이미 방문한 상태면 스킵
            if (visited[next_redX][next_redY][next_blueX][next_blueY]) continue;

            visited[next_redX][next_redY][next_blueX][next_blueY] = true;
            q.push({next_redX, next_redY, next_blueX, next_blueY, next_depth});
        }
    }

    // 성공 못하면 -1
    cout << -1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int redX = 0, redY = 0;
    int blueX = 0, blueY = 0;

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        string row;
        cin >> row;
        for (int j = 0; j < m; j++) {
            board[i][j] = row[j];
            if (row[j] == 'R') {
                redX = i;
                redY = j;
            } else if (row[j] == 'B') {
                blueX = i;
                blueY = j;
            }
        }
    }

    // 시작 상태
    q.push({redX, redY, blueX, blueY, 0});
    visited[redX][redY][blueX][blueY] = true;

    bfs();
}