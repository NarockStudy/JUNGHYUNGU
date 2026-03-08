#include <iostream>
#include <vector>
using namespace std;

struct Shark {
    int y, x;
    int s, d, z;
    bool dead = false;
};

int dx[] = {0, 0, 0, 1, -1};
int dy[] = {0, -1, 1, 0, 0};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int r, c, m;
    int answer = 0;
    cin >> r >> c >> m;

    vector<vector<int>> board(r + 1, vector<int>(c + 1, 0));
    vector<Shark> shark(m + 1);

    // 상어 초기 위치 저장
    for (int i = 1; i <= m; i++) {
        cin >> shark[i].y >> shark[i].x >> shark[i].s >> shark[i].d >> shark[i].z;
        board[shark[i].y][shark[i].x] = i;
    }

    // 낚시왕이 왼쪽 → 오른쪽으로 이동
    for (int t = 1; t <= c; t++) {

        // 현재 열에서 가장 가까운 상어 잡기
        for (int k = 1; k <= r; k++) {
            if (board[k][t] != 0) {
                int idx = board[k][t];
                shark[idx].y = -1;
                shark[idx].x = -1;
                shark[idx].dead = true;
                answer += shark[idx].z;
                board[k][t] = 0;
                break;
            }
        }

        // 모든 상어 이동
        for (int i = 1; i <= m; i++) {
            if (shark[i].dead) continue;

            // 위 / 아래 이동
            if (shark[i].d == 1 || shark[i].d == 2) {
                if (r > 1) {
                    int cycle = 2 * r - 2;   // 왕복 이동 주기
                    int move = shark[i].s % cycle;

                    int ny = shark[i].y + move * dy[shark[i].d];

                    // 경계에 부딪히면 방향 반전
                    while (ny < 1 || ny > r) {
                        if (ny > r) {
                            ny = 2 * r - ny;
                            shark[i].d = 1;
                        } 
                        
                        else {
                            ny = 2 - ny;
                            shark[i].d = 2;
                        }
                    }
                    shark[i].y = ny;
                }
            }
            // 좌 / 우 이동
            else {
                if (c > 1) {
                    int cycle = 2 * c - 2;
                    int move = shark[i].s % cycle;

                    int nx = shark[i].x + move * dx[shark[i].d];

                    while (nx < 1 || nx > c) {
                        if (nx > c) {
                            nx = 2 * c - nx;
                            shark[i].d = 4;
                        } 
                        
                        else {
                            nx = 2 - nx;
                            shark[i].d = 3;
                        }
                    }
                    shark[i].x = nx;
                }
            }
        }

        // 보드 초기화 (새 위치 다시 기록)
        board.assign(r + 1, vector<int>(c + 1, 0));

        // 같은 칸에 여러 상어가 있으면 큰 상어만 생존
        for (int i = 1; i <= m; i++) {
            if (shark[i].dead) continue;

            int cy = shark[i].y;
            int cx = shark[i].x;

            if (board[cy][cx] == 0) {
                board[cy][cx] = i;
            } 
            
            else {
                int other = board[cy][cx];

                if (shark[other].z < shark[i].z) {
                    shark[other].y = -1;
                    shark[other].x = -1;
                    shark[other].dead = true;
                    board[cy][cx] = i;
                } else {
                    shark[i].y = -1;
                    shark[i].x = -1;
                    shark[i].dead = true;
                }
            }
        }
    }

    cout << answer;
    return 0;
}