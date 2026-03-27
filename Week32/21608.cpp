#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int n;

struct seat {
    int y, x;
    int empty_cnt, like_cnt;

    bool operator<(const seat& other) const {
        // 좋아하는 학생 수 우선
        if (like_cnt != other.like_cnt) return like_cnt > other.like_cnt;
        // 인접한 빈칸 수 우선
        if (empty_cnt != other.empty_cnt) return empty_cnt > other.empty_cnt;
        // 행이 작은 칸 우선
        if (y != other.y) return y < other.y;
        // 열이 작은 칸 우선
        return x < other.x;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;

    vector<vector<int>> board(n, vector<int>(n, 0));
    vector<int> order;
    map<int, vector<int>> like;

    for (int i = 0; i < n * n; i++) {
        int s, a, b, c, d;
        cin >> s >> a >> b >> c >> d;

        order.push_back(s);
        like[s] = {a, b, c, d};
    }

    // 학생을 입력 순서대로 배치
    for (int s : order) {
        vector<seat> cand;

        for (int y = 0; y < n; y++) {
            for (int x = 0; x < n; x++) {
                if (board[y][x] != 0) continue;

                int like_cnt = 0;
                int empty_cnt = 0;

                // 현재 빈칸 기준 상하좌우 확인
                for (int dir = 0; dir < 4; dir++) {
                    int ny = y + dy[dir];
                    int nx = x + dx[dir];

                    if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;

                    if (board[ny][nx] == 0) {
                        empty_cnt++;
                    } else {
                        if (find(like[s].begin(), like[s].end(), board[ny][nx]) != like[s].end()) {
                            like_cnt++;
                        }
                    }
                }

                cand.push_back({y, x, empty_cnt, like_cnt});
            }
        }

        sort(cand.begin(), cand.end());
        board[cand[0].y][cand[0].x] = s;
    }

    int answer = 0;

    // 모든 학생의 만족도 계산
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            int s = board[y][x];
            int cnt = 0;

            for (int dir = 0; dir < 4; dir++) {
                int ny = y + dy[dir];
                int nx = x + dx[dir];
                if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
                if (find(like[s].begin(), like[s].end(), board[ny][nx]) != like[s].end()) cnt++;
            }

            if (cnt == 1) answer += 1;
            else if (cnt == 2) answer += 10;
            else if (cnt == 3) answer += 100;
            else if (cnt == 4) answer += 1000;
        }
    }

    cout << answer;
    return 0;
}