#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int n, m, k;
int answer = INT_MAX;

int rotationInfo[6][3];
bool used[6] = {false,};

int original[51][51];
int board[51][51];
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

vector<int> rotationOrder;

// 현재 board에서 각 행의 합 중 최솟값 계산
int getMinRowSum() {
    int minRowSum = INT_MAX;

    for (int i = 1; i <= n; i++) {
        int rowSum = 0;
        for (int j = 1; j <= m; j++) {
            rowSum += board[i][j];
        }
        minRowSum = min(minRowSum, rowSum);
    }

    return minRowSum;
}

// idx번 회전 연산을 board에 적용
void rotateArray(int idx) {
    // 아래, 오른쪽, 위, 왼쪽 순서로 탐색
    // 현재 칸에 "다음 칸의 값"을 가져오면 결과적으로 시계 방향 회전이 됨
    int r = rotationInfo[idx][0];
    int c = rotationInfo[idx][1];
    int s = rotationInfo[idx][2];

    int startX = r - s, startY = c - s;
    int endX = r + s, endY = c + s;

    // 겹(layer) 수만큼 회전
    int layerCount = (endX - startX + 1) / 2;

    for (int layer = 0; layer < layerCount; layer++) {
        int top = startX + layer;
        int bottom = endX - layer;
        int left = startY + layer;
        int right = endY - layer;

        int x = top;
        int y = left;
        int saved = board[x][y];  // 시작 값을 따로 저장

        int dir = 0;
        while (dir < 4) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            // 현재 layer 범위를 벗어나면 방향 전환
            if (nx < top || nx > bottom || ny < left || ny > right) {
                dir++;
                continue;
            }

            // 다음 칸의 값을 현재 칸으로 당겨옴
            board[x][y] = board[nx][ny];
            x = nx;
            y = ny;
        }

        // 마지막 비어 있는 자리에 처음 저장한 값 삽입
        board[top][left + 1] = saved;
    }
}

// 모든 회전 순열 생성
void backtrack(int depth) {
    // k개의 연산 순서가 모두 정해진 경우
    if (depth == k) {
        // 원본 배열 복사
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                board[i][j] = original[i][j];
            }
        }

        // 정해진 순서대로 회전 적용
        for (int idx : rotationOrder) {
            rotateArray(idx);
        }

        // 행 합 최솟값 갱신
        answer = min(answer, getMinRowSum());
        return;
    }

    for (int i = 0; i < k; i++) {
        if (used[i]) continue;

        used[i] = true;
        rotationOrder.push_back(i);

        backtrack(depth + 1);

        rotationOrder.pop_back();
        used[i] = false;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> original[i][j];
        }
    }

    for (int i = 0; i < k; i++) {
        int r, c, s;
        cin >> r >> c >> s;
        rotationInfo[i][0] = r;
        rotationInfo[i][1] = c;
        rotationInfo[i][2] = s;
    }

    backtrack(0);

    cout << answer;
    return 0;
}