#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;  

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int arr[505][505] = {0, };
bool visited[505][505] = {false, };
int answer = 0;

void dfs(int x, int y, int cnt, int sum) {
    // 현재 칸 방문 처리
    visited[y][x] = true;
    sum += arr[y][x];

    // 테트로미노 4칸을 모두 선택한 경우
    if (cnt == 4) {
        answer = max(answer, sum);
        visited[y][x] = false;
        return;
    }

    // ㅗ 모양 제외한 나머지 도형은 DFS로 탐색 가능
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        // 범위를 벗어나면 스킵
        if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;

        // 이미 방문한 칸이면 스킵
        if (visited[ny][nx]) continue;

        dfs(nx, ny, cnt + 1, sum);
    }

    // 백트래킹
    visited[y][x] = false;
}

void checkT(int x, int y) {
    // ㅗ, ㅜ, ㅓ, ㅏ 모양은 일반 DFS 경로로 만들 수 없어서 별도 처리

    // ㅓ 모양
    if (x - 1 >= 0 && y - 1 >= 0 && y + 1 < n) {
        answer = max(answer,
            arr[y][x] + arr[y - 1][x] + arr[y + 1][x] + arr[y][x - 1]);
    }

    // ㅏ 모양
    if (x + 1 < m && y - 1 >= 0 && y + 1 < n) {
        answer = max(answer,
            arr[y][x] + arr[y - 1][x] + arr[y + 1][x] + arr[y][x + 1]);
    }

    // ㅗ 모양
    if (x - 1 >= 0 && x + 1 < m && y - 1 >= 0) {
        answer = max(answer,
            arr[y][x] + arr[y][x - 1] + arr[y][x + 1] + arr[y - 1][x]);
    }

    // ㅜ 모양
    if (x - 1 >= 0 && x + 1 < m && y + 1 < n) {
        answer = max(answer,
            arr[y][x] + arr[y][x - 1] + arr[y][x + 1] + arr[y + 1][x]);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    // arr[y][x] 형태로 입력
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) {
            cin >> arr[y][x];
        }
    }

    // 모든 칸을 시작점으로 탐색
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) {
            dfs(x, y, 1, 0);  // 시작 칸 포함이므로 cnt = 1
            checkT(x, y);     // ㅗ 계열 별도 처리
        }
    }

    cout << answer;
}