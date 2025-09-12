#include <iostream>

using namespace std;

bool chess[10][10];
bool visited1[20];        // ↘ 방향 대각선(좌상→우하) 체크
bool visited2[20];        // ↙ 방향 대각선(우상→좌하) 체크
int king[2];
int chess_size;

// 백트래킹: 현재 위치(x,y)에서 비숍을 두거나 두지 않고 진행
// 색(color) = 0(검정칸), 1(하얀칸) → 대각선끼리 겹치지 않게 탐색
void track(int count, int x, int y, int color){
    if(x >= chess_size){
        y++;         // 다음 줄로 이동할 때 색깔 패턴 유지 (짝수/홀수 칸 건너뛰기)
        if(x % 2 == 0) x = 1;
        else x = 0;
    }
    if ( y >= chess_size){
        // 해당 색에서의 최대 비숍 수 갱신
        king[color] = max(king[color], count);
        return;
    }
    // 현재 칸에 비숍을 놓을 수 있는 경우
    if(chess[y][x] && !visited1[x + y + 1] && !visited2[x - y + chess_size]){
        visited1[x + y + 1] = 1;
        visited2[x - y + chess_size] = 1;
        track(count + 1, x + 2, y, color); // 비숍 놓고 다음 칸 탐색
        visited1[x + y + 1] = 0;
        visited2[x - y + chess_size] = 0;
    }
    // 현재 칸에 비숍을 놓지 않고 진행
    track(count, x + 2, y, color);
}

int main(){
    cin >> chess_size;

    for(int i = 0; i < chess_size; i++)
        for(int j = 0; j < chess_size; j++) cin >> chess[i][j];

    // 검정 칸(0,0부터 시작)과 흰 칸(0,1부터 시작) 따로 탐색
    track(0,0,0,0); track(0,1,0,1);

    // 두 색 결과 합산 = 전체 최대 비숍 개수
    cout << king[0] + king[1];
}