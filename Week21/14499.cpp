#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int board[20][20];
int dice[6];
int n, m, x, y, k;

int move(int dir){
    if(dir == 1 && y + 1 < m){ // 동쪽 이동
        y++;
        return 1;
    }
    else if(dir == 2 && y - 1 >= 0){ // 서쪽 이동
        y--;
        return 1;
    }
    else if(dir == 3 && x - 1 >= 0){ // 북쪽 이동
        x--;
        return 1;
    }
    else if(dir == 4 && x + 1 < n){ // 남쪽 이동
        x++;
        return 1;
    }

    return 0;
}
void rotate(int dir){
    int temp = dice[0]; // 아래면 저장

    if(dir == 1){ // 동쪽
        dice[0] = dice[3]; // 아래 <- 서
        dice[3] = dice[1]; // 서 <- 위
        dice[1] = dice[2]; // 위 <- 동
        dice[2] = temp;    // 동 <- 이전 아래
    }
    else if(dir == 2){ // 서쪽
        dice[0] = dice[2]; // 아래 <- 동
        dice[2] = dice[1]; // 동 <- 위
        dice[1] = dice[3]; // 위 <- 서
        dice[3] = temp;    // 서 <- 이전 아래
    }
    else if(dir == 3){ // 북쪽
        dice[0] = dice[5]; // 아래 <- 남
        dice[5] = dice[1]; // 남 <- 위
        dice[1] = dice[4]; // 위 <- 북
        dice[4] = temp;    // 북 <- 이전 아래
    }
    else if(dir == 4){ // 남쪽
        dice[0] = dice[4]; // 아래 <- 북
        dice[4] = dice[1]; // 북 <- 위
        dice[1] = dice[5]; // 위 <- 남
        dice[5] = temp;    // 남 <- 이전 아래
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> x >> y >> k;   
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)cin >> board[i][j];
    int dir;
    for(int i = 0; i < k; i++)
    {
        cin >> dir;
        if(move(dir)){
            rotate(dir);
        
        if(board[x][y]){
            dice[0] = board[x][y];
            board[x][y] = 0;
        }
        else { board[x][y] = dice[0]; }
        cout << dice[1] << "\n";
    }
    }
    return 0;

}