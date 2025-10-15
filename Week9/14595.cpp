#include <iostream>
using namespace std;

int n, m;
int arr[1'000'005];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int answer = 0;
    cin >> n >> m;

    // 각 구간 [x, y) 에 대해 차이 배열(diff array) 방식으로 표시
    while (m--) {
        int x, y;
        cin >> x >> y;
        arr[x]++;    // 구간 시작점: +1
        arr[y]--;    // 구간 끝점: -1 (y는 포함 안 함)
    }

    // 누적합을 구하며 각 위치가 덮였는지 여부 확인
    for (int i = 1; i <= n; i++) {
        arr[i] += arr[i - 1];   // 현재 구간에 포함된 횟수 누적
        if (!arr[i]) answer++;  // 값이 0 → 어떤 구간에도 속하지 않음
    }

    // 덮이지 않은 구간(빈 구간)의 개수 출력
    cout << answer;
}
