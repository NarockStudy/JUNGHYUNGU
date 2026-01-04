#include <iostream>
#include <vector>
using namespace std;

// 방향: 0→, 1↑, 2←, 3↓
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

int n;
vector<vector<int>> v(105, vector<int>(105, 0)); // 드래곤 커브가 지나간 좌표 표시

int dragon_curve() {
    int dragon = 0;
    for (int x = 0; x < 100; x++) {
        for (int y = 0; y < 100; y++) {
            // 네 꼭짓점이 모두 방문된 경우
            if (v[x][y] && v[x + 1][y] && v[x][y + 1] && v[x + 1][y + 1])
                dragon++;
        }
    }
    return dragon;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    while (n--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        vector<int> v2;
        v2.push_back(c); // 0세대 방향 저장

        // 드래곤 커브 방향 생성 (뒤집어서 +1 회전)
        for (int i = 0; i < d; i++) {
            int sz = v2.size();
            for (int j = sz - 1; j >= 0; j--)
                v2.push_back((v2[j] + 1) % 4);
        }

        // 시작점 표시
        v[a][b] = 1;

        // 방향대로 이동하며 좌표 기록
        for (auto dir : v2) {
            a += dx[dir];
            b += dy[dir];
            v[a][b] = 1;
        }
    }

    cout << dragon_curve(); 
}
