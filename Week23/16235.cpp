#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, k;

int soil[11][11];
int addnutr[11][11];

vector<int> trees[11][11];

// dead_tree[x][y] : 봄에 죽은 나무들이 여름에 줄 양분(나이/2 누적)
int dead_tree[11][11];

int dx[8] = {0,0,1,-1, 1,-1, 1,-1};
int dy[8] = {1,-1,0,0, 1,-1,-1, 1};

// 1) 봄: 어린 나무부터 양분 먹고 나이 +1, 못 먹으면 죽음(여름 양분으로 전환될 값 누적)
void spring() {
    for(int x = 1; x <= n; x++) {
        for(int y = 1; y <= n; y++) {
            if(trees[x][y].empty()) continue;

            sort(trees[x][y].begin(), trees[x][y].end()); // 어린 순

            vector<int> v;
            v.reserve(trees[x][y].size());

            for(int age : trees[x][y]) {
                if(soil[x][y] >= age) {
                    soil[x][y] -= age;        // 나이만큼 양분 소비
                    v.push_back(age + 1); // 생존 + 나이 증가
                } else {
                    dead_tree[x][y] += age / 2; // 사망 → 여름에 양분으로
                }
            }

            trees[x][y].swap(v); // 생존 리스트로 교체 (erase 반복 제거)
        }
    }
}

// 2) 여름: 죽은 나무들이 양분이 되어 soil에 더해짐
void summer() {
    for(int x = 1; x <= n; x++) {
        for(int y = 1; y <= n; y++) {
            soil[x][y] += dead_tree[x][y];
            dead_tree[x][y] = 0;
        }
    }
}

// 3) 가을: 나이가 5의 배수인 나무가 인접 8칸에 나이 1 나무 번식
void fall() {
    for(int x = 1; x <= n; x++) {
        for(int y = 1; y <= n; y++) {
            if(trees[x][y].empty()) continue;

            for(int age : trees[x][y]) {
                if(age % 5 != 0) continue;

                for(int dir = 0; dir < 8; dir++) {
                    int nx = x + dx[dir];
                    int ny = y + dy[dir];
                    if(nx < 1 || ny < 1 || nx > n || ny > n) continue;

                    trees[nx][ny].push_back(1); // 새 나무(나이 1) 추가
                }
            }
        }
    }
}

// 4) 겨울: 각 칸에 addnutr 만큼 양분 추가
void winter() {
    for(int x = 1; x <= n; x++)
        for(int y = 1; y <= n; y++)
            soil[x][y] += addnutr[x][y];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;

    // 초기 양분: 모든 칸 5, 겨울 추가양분 입력
    for(int x = 1; x <= n; x++) {
        for(int y = 1; y <= n; y++) {
            cin >> addnutr[x][y];
            soil[x][y] = 5;
        }
    }

    // 초기 나무 입력 (x, y, age)
    for(int i = 0; i < m; i++) {
        int x, y, age;
        cin >> x >> y >> age;
        trees[x][y].push_back(age);
    }

    // k년 시뮬레이션
    for(int year = 0; year < k; year++) {
        spring();
        summer();
        fall();
        winter();
    }

    // 남은 나무 개수 합산
    long long answer = 0;
    for(int x = 1; x <= n; x++)
        for(int y = 1; y <= n; y++)
            answer += (long long)trees[x][y].size();

    cout << answer;
}
