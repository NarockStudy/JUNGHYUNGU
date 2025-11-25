#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

#define X first
#define Y second

int n, m;
bool visit[13];                    
int board[51][51];
vector<pair<int, int>> house;      
vector<pair<int, int>> chicken;    
int answer = INT_MAX;

// 선택된 M개의 치킨집으로부터 도시 치킨 거리 계산
int dist() {
    int total = 0;
    for (int i = 0; i < house.size(); i++) {
        int hx = house[i].X, hy = house[i].Y;
        int min_dist = INT_MAX;

        // 선택된 치킨집 중 가장 가까운 거리 찾기
        for (int j = 0; j < chicken.size(); j++) {
            if (!visit[j]) continue;
            int cx = chicken[j].X, cy = chicken[j].Y;
            int d = abs(hx - cx) + abs(hy - cy);
            min_dist = min(min_dist, d);
        }
        total += min_dist;
    }
    return total;
}

// 조합 DFS: 치킨집 중 M개 선택
void dfs(int idx, int count) {
    if (count == m) {                   // M개 선택되면 거리 계산
        answer = min(answer, dist());
        return;
    }

    // idx부터 치킨집 선택 시작
    for (int i = idx; i < chicken.size(); i++) {
        visit[i] = true;
        dfs(i + 1, count + 1);
        visit[i] = false;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    // 집과 치킨집 위치 저장
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
            if (board[i][j] == 1) house.push_back({i, j});
            else if (board[i][j] == 2) chicken.push_back({i, j});
        }
    }

    dfs(0, 0);            // 치킨집 조합 탐색 시작
    cout << answer;
}
