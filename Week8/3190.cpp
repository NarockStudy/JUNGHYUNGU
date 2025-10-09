#include <iostream>
#include <vector>
#include <queue>
#include <deque>
using namespace std;

#define X first
#define Y second

int n, k, l;
int arr[105][105]; 


int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;
    for (int i = 0; i < k; i++) {
        int a, b;
        cin >> a >> b;
        arr[a][b] = 2; 
    }

    cin >> l;
    queue<pair<int, char>> rot;
    for (int i = 0; i < l; i++) {
        int t; char c;
        cin >> t >> c;
        rot.push({t, c});
    }

    deque<pair<int, int>> snake; 
    snake.push_back({1, 1});
    arr[1][1] = 1;

    int time = 0, dir = 0; 
    
    while (true) {
        time++;

        // 머리를 한 칸 이동
        int nx = snake.back().X + dx[dir];
        int ny = snake.back().Y + dy[dir];

        // 벽 또는 자기 자신과 충돌하면 종료
        if (nx <= 0 || ny <= 0 || nx > n || ny > n || arr[nx][ny] == 1) break;

        // 사과가 없으면 꼬리 제거
        if (arr[nx][ny] != 2) {
            auto tail = snake.front();
            snake.pop_front();
            arr[tail.X][tail.Y] = 0;
        }

        // 머리 이동
        snake.push_back({nx, ny});
        arr[nx][ny] = 1;

        // 회전 시점 체크
        if (!rot.empty() && time == rot.front().X) {
            if (rot.front().Y == 'D') dir = (dir + 1) % 4;          // 오른쪽 회전
            else dir = (dir + 3) % 4;                               // 왼쪽 회전
            rot.pop();
        }
    }

    cout << time;
}
