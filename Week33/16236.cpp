#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

int n;
int map[25][25];
int dx[] = {0, -1, 1, 0}; 
int dy[] = {-1, 0, 0, 1};

int bx, by;
int answer;          
bool stop = false;
bool eat = false;

void bfs(int a, int b, bool visit[][25], int shSize) {
    queue<pair<pair<int, int>, int>> q;
    q.push({{a, b}, 0});
    visit[b][a] = true;

    int minDist = -1;
    int fishX = -1, fishY = -1;

    while (!q.empty()) {
        int x = q.front().first.first;
        int y = q.front().first.second;
        int cnt = q.front().second;
        q.pop();

        // 이미 더 가까운 물고기를 찾았으면 그 거리보다 먼 곳은 볼 필요 없음
        if (minDist != -1 && cnt > minDist) break;

        // 먹을 수 있는 물고기 발견
        if (map[y][x] > 0 && map[y][x] < shSize) {
            if (minDist == -1) {
                minDist = cnt;
                fishX = x;
                fishY = y;
            } else {
                if (y < fishY || (y == fishY && x < fishX)) {
                    fishX = x;
                    fishY = y;
                }
            }
            continue;
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < n && ny >= 0 && ny < n && !visit[ny][nx]) {
                if (map[ny][nx] <= shSize) {
                    visit[ny][nx] = true;
                    q.push({{nx, ny}, cnt + 1});
                }
            }
        }
    }

    if (minDist != -1) {
        eat = true;
        bx = fishX;
        by = fishY;
        answer += minDist;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> map[i][j];
            if (map[i][j] == 9) {
                by = i;
                bx = j;
                map[i][j] = 0;
            }
        }
    }

    int size = 2, count = 0;

    while (!stop) {
        bool visit[25][25] = {0};
        bfs(bx, by, visit, size);

        if (eat) {
            eat = false;
            count++;
            map[by][bx] = 0;

            if (count == size) {
                size++;
                count = 0;
            }
        } else stop = true;
    }

    cout << answer;
    return 0;
}