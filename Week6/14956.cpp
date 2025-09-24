#include <iostream>

using namespace std;

pair<int,int> hilbert(int n, int k){
    // 기저: 2x2 격자에서의 방문 순서(1..4)
    // (1) (1,1) → (2) (1,2) → (3) (2,2) → (4) (2,1)
    if (n == 2) {
        if (k == 1) return {1,1};
        if (k == 2) return {1,2};
        if (k == 3) return {2,2};
        return {2,1}; // k == 4
    }

    int half = n / 2;           
    int block_size = half * half; 

    // 어느 사분면(0..3)에 K가 들어가는지 판별
    // cur == 0: 첫번째 블록(왼쪽-상단)
    // cur == 1: 두번째 블록(오른쪽-상단)
    // cur == 2: 세번째 블록(오른쪽-하단)
    // cur == 3: 네번째 블록(왼쪽-하단)
    int cur = (k - 1) / block_size;

    if (cur == 0) {
        // 좌상단 블록: 이 블록은 "회전"이 필요 → 내부 좌표는 재귀로 구하고 (r,c) -> (c, r)
        // 이유: Hilbert 패턴이 좌상단에서 시작할 때 하위 곡선을 90도 회전해서 연결
        auto p = hilbert(half, k);      // 반쪽 크기에서 해당 순서 위치 (1..half)
        return {p.second, p.first};     // x,y를 교환(회전)
    } 
    else if (cur == 1) {
        // 우상단 블록: 내부 좌표를 구한 뒤 열(col)에 half를 더해 오른쪽으로 이동
        auto p = hilbert(half, k - block_size);
        return {p.first, p.second + half};
    } 
    else if (cur == 2) {
        // 우하단 블록: 내부 좌표에 행(row), 열(col) 둘 다 half를 더해 아래 오른쪽으로 이동
        auto p = hilbert(half, k - 2 * block_size);
        return {p.first + half, p.second + half};
    } 
    else { // cur == 3
        // 좌하단 블록: 특수한 회전+대칭 변환 필요
        // 하위 패턴에서 얻은 (r,c)를 변환하여 좌하단의 Hilbert 순서에 맞게 배치
        // 변환 공식: return { 2*half - c + 1, half - r + 1 }
        // - 이 변환은 하위 블록을 반시계 회전하고 좌표계를 맞추는 역할을 함
        auto p = hilbert(half, k - 3 * block_size);
        return {2 * half - p.second + 1, half - p.first + 1};
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    // Hilbert 함수는 1-indexed 좌표를 반환하므로 그대로 출력
    auto ans = hilbert(N, K);
    cout << ans.first << " " << ans.second << "\n";
    return 0;
}