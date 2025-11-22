#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

int n, m, k;

int dx[] = {0, 0, -1, 1, 1, 1, -1, -1};
int dy[] = {1, -1, 0, 0, 1, -1, 1, -1};

map<string, int> result;        
vector<vector<char>> v;         
string s;                      

// DFS: 현재 위치 (x, y)에서 문자열 s를 확장하며 탐색
void dfs(int x, int y) {
    // 문제 조건상 문자열 최대 길이는 5
    if (s.length() > 5) return;

    // s가 찾을 문자열 목록에 있으면 카운트 증가
    if (auto it = result.find(s); it != result.end()) {
        it->second++;
    }

    // 8 방향으로 DFS 확장
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        // 격자 밖으로 나가면 반대편으로 워프
        if (nx >= n) nx = 0;
        if (nx < 0) nx = n - 1;
        if (ny >= m) ny = 0;
        if (ny < 0) ny = m - 1;

        // 새 문자 추가하고 DFS
        s.push_back(v[nx][ny]);
        dfs(nx, ny);

        // DFS 후 복구
        s.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;

    // 문자 격자 입력
    v.assign(n, vector<char>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> v[i][j];

    // 찾을 문자열 목록 입력
    vector<string> searchList;
    searchList.reserve(k);

    for (int i = 0; i < k; i++) {
        string x;
        cin >> x;
        searchList.push_back(x);
        result[x] = 0; // 초기 카운트 0으로 삽입
    }

    // 격자 모든 칸에서 DFS 시작
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            s = "";                        // 시작 문자열 초기화
            s.push_back(v[i][j]);          // 시작 문자 추가
            dfs(i, j);                     // DFS 실행
        }
    }

    // 입력한 순서대로 결과 출력
    for (const string &word : searchList)
        cout << result[word] << "\n";

    return 0;
}
