#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int board[51][51];
bool checked[51][51];

int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};
int n,m,r,c,d;

// d: 0=북, 1=동, 2=남, 3=서
// 로봇은 반시계 방향으로 회전하므로
// 왼쪽으로 회전할 때는 (d+3)%4 를 사용한다.

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> r >> c >> d;
    int answer = 0;

    for(int i = 0; i < n; i++)
        for(int j = 0 ; j < m; j++) cin >> board[i][j];


    
    while(1){
        // 현재 칸이 아직 청소되지 않았다면 청소
        if(!checked[r][c]){
            checked[r][c] = 1; answer++;
        }
        bool ch = false;

        // 현재 방향을 기준으로 왼쪽부터 차례대로 탐색 (최대 4번)
        for(int i = 0 ; i < 4; i++){
            d = (d+3) % 4;
            int nx = r + dx[d];
            int ny = c + dy[d];

            // 왼쪽 방향에 청소할 수 있는 공간이 있다면 이동
            if(!board[nx][ny] && !checked[nx][ny]){
                r += dx[d];
                c += dy[d];
                ch = true; break;

            }
        }

        // 네 방향 모두 청소할 곳이 없는 경우
        if(!ch){
            int back = (d+2) % 4;

            // 후진했을 때 벽이면 종료
            if (board[r + dx[back]][c + dy[back]]) break;
            r += dx[back];
            c += dy[back];
        }
    }
    cout << answer;
}