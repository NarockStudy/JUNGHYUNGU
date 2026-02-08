#include <bits/stdc++.h>
using namespace std;

static const int INF = 1000000000;

int N, M;
int board[50][50];

vector<pair<int,int>> virus;
vector<pair<int,int>> active;

int arr[50][50];
int dr[4] = {1, -1, 0, 0};
int dc[4] = {0, 0, 1, -1};

int best = INF;
int emptyCnt = 0;

// 선택된 바이러스(active)를 시작점으로 BFS를 돌려
// 벽(1)을 제외한 모든 칸(0 + 2)이 감염되기까지 걸리는 최소 시간 계산
void bfs() {
    memset(arr, -1, sizeof(arr));

    queue<pair<int,int>> q;

    // 활성 바이러스는 시작 시점(시간 0)으로 큐에 삽입
    for (int i = 0; i < (int)active.size(); i++) {
        int r = active[i].first;
        int c = active[i].second;
        arr[r][c] = 0;
        q.push(active[i]);
    }

    // 이미 감염된 칸 수 (시작 바이러스 포함)
    int infectedEmpty = (int)active.size();
    int timeMax = 0;

    // 시작점만으로 모든 대상이 감염된 경우
    if (infectedEmpty == emptyCnt) {
        best = min(best, 0);
        return;
    }

    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];

            if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
            if (board[nr][nc] == 1) continue;     // 벽은 확산 불가
            if (arr[nr][nc] != -1) continue;      // 이미 방문한 칸

            arr[nr][nc] = arr[r][c] + 1;
            q.push({nr, nc});

            // 벽이 아닌 모든 칸(0, 2)을 감염 대상으로 처리
            infectedEmpty++;
            timeMax = max(timeMax, arr[nr][nc]);

            // 모든 대상 칸이 감염되면 해당 조합의 최소 시간 확정
            if (infectedEmpty == emptyCnt) {
                best = min(best, timeMax);
                return;
            }
        }
    }
}

// 바이러스 후보 중 M개를 선택하는 조합 생성
void choose(int idx) {
    if ((int)active.size() == M) {
        bfs();
        return;
    }
    if (idx == (int)virus.size()) return;

    int remaining = (int)virus.size() - idx;
    int need = M - (int)active.size();
    if (remaining < need) return;

    // 현재 idx 바이러스를 선택하지 않는 경우
    choose(idx + 1);

    // 현재 idx 바이러스를 선택하는 경우
    active.push_back(virus[idx]);
    choose(idx + 1);
    active.pop_back();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            cin >> board[r][c];
            if (board[r][c] == 2) virus.push_back({r, c});
            if (board[r][c] != 1) emptyCnt++; // 벽을 제외한 모든 칸을 감염 대상로 계산
        }
    }

    // 감염 대상이 없는 경우
    if (emptyCnt == 0) {
        cout << 0;
        return 0;
    }

    choose(0);

    cout << (best == INF ? -1 : best);
    return 0;
}