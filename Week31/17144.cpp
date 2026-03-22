#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define X first
#define Y second

int r, c, t;
int board[50][50];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

void air_cleaner(pair<int, int> cleaner, int dir) {
    pair<int, int> cur = cleaner;

    while (true) {
        pair<int, int> nextPos = {cur.X + dx[dir], cur.Y + dy[dir]};

        // 범위 벗어나거나 끝 도달 → 방향 전환
        if (nextPos.X < 0 || nextPos.Y < 0 || nextPos.X >= r || nextPos.Y >= c ||
            (cur.X == cleaner.X && cur.Y == c - 1)) {

            if (board[cleaner.X - 1][cleaner.Y] == -1) {
                dir = (dir == 0) ? 3 : dir - 1;  // 반시계
            } else {
                dir = (dir + 1) % 4;             // 시계
            }

            nextPos = {cur.X + dx[dir], cur.Y + dy[dir]};
        }

        // 공기청정기 도달 → 종료
        if (nextPos.X == cleaner.X && nextPos.Y == cleaner.Y) {
            board[cur.X][cur.Y] = 0;
            break;
        }

        if (cur.X == cleaner.X && cur.Y == cleaner.Y) {
            board[nextPos.X][nextPos.Y] = 0;
        } else {
            board[cur.X][cur.Y] = board[nextPos.X][nextPos.Y];
        }

        cur = nextPos;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> r >> c >> t;

    pair<int, int> lowerCleaner;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> board[i][j];
            if (board[i][j] == -1) {
                lowerCleaner = {i, j};
            }
        }
    }

    int time = 0;

    while (time < t) {
        int spread[50][50];
        fill(&spread[0][0], &spread[49][50], 0);

        // 1. 확산
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (board[i][j] > 0) {
                    int spreadCount = 0;

                    for (int dir = 0; dir < 4; dir++) {
                        pair<int, int> nextPos = {i + dx[dir], j + dy[dir]};

                        if (nextPos.X < 0 || nextPos.Y < 0 || nextPos.X >= r || nextPos.Y >= c)
                            continue;
                        if (board[nextPos.X][nextPos.Y] == -1)
                            continue;

                        spread[nextPos.X][nextPos.Y] += board[i][j] / 5;
                        spreadCount++;
                    }

                    board[i][j] -= (board[i][j] / 5) * spreadCount;
                }
            }
        }

        // 확산 반영
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                board[i][j] += spread[i][j];

        // 2. 공기청정기 작동
        air_cleaner({lowerCleaner.X - 1, lowerCleaner.Y}, 0); // 위
        air_cleaner(lowerCleaner, 2);                         // 아래

        time++;
    }

    int answer = 0;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            if (board[i][j] != -1)
                answer += board[i][j];

    cout << answer;
}