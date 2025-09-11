#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

int gaaaaarden[51][51];
int dx[4] = {0,0,-1,1};
int dy[4] = {1,-1,0,0};

int n,m,g,r;
int answer;

// BFS: 주어진 배치에서 초록/빨강 확산을 시뮬레이션하고 꽃이 몇 개 생기는지 반환
int bfs(){
    int tmp[51][51];
    queue<pair<int, int>> gq, rq;
    int rd[51][51];
    int gd[51][51];
    bool flowers[51][51];
    int flower_count = 0;
    memset(rd, 0, sizeof(rd));
    memset(gd, 0, sizeof(gd));
    memset(flowers, false, sizeof(flowers));

    // 초기 배양액 위치 세팅 (3=초록, 4=빨강)
    for(int i = 1; i<=n; i++){
        for(int j = 1; j<= m; j++){
            if(gaaaaarden[i][j] == 3){
                gq.push({i,j});
                gd[i][j] = 1;
            }
            if(gaaaaarden[i][j] == 4){
                rq.push({i,j});
                rd[i][j] = 1;
            }
            tmp[i][j] = gaaaaarden[i][j];
        }
    }

    // 두 큐가 모두 빌 때까지 확산 진행
    while(!gq.empty() || !rq.empty()){
        int gq_size = gq.size();
        int rq_size = rq.size();

        // 초록 확산
        while(gq_size--){
            int x = gq.front().first;
            int y = gq.front().second; gq.pop();
            if(flowers[x][y]) continue;
            for(int i = 0; i < 4; i++){
                int nx = x + dx[i];
                int ny = y + dy[i];
                if(1 <= nx && nx <= n && 1 <= ny && ny <= m){
                    if ((tmp[nx][ny] == 1 || tmp[nx][ny] == 2) && !flowers[nx][ny] && !gd[nx][ny] && !rd[nx][ny]){
                        gd[nx][ny] = gd[x][y] + 1;
                        gq.push({ nx,ny });
                    }
                }
            }
        }

        // 빨강 확산
        while(rq_size--){
            int x = rq.front().first;
            int y = rq.front().second; rq.pop();
            if(flowers[x][y]) continue;
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (1 <= nx && nx <= n && 1 <= ny && ny <= m) {
                    if ((tmp[nx][ny] == 1 || tmp[nx][ny] == 2) && !flowers[nx][ny] && !rd[nx][ny]){
                        // 초록과 동시에 도착하면 꽃 생성
                        if (gd[nx][ny] == rd[x][y] + 1) {
                            flowers[nx][ny] = true;
                            flower_count++;
                        }
                        else {
                            rd[nx][ny] = rd[x][y] + 1;
                            rq.push({ nx,ny });
                        }
                    }
                }
            }
        }
    }
    return flower_count;
}

// comb: 배양액을 놓을 위치 조합을 생성하고 최대 꽃 개수 갱신
void comb(int g, int r, int x, int y){
    if (g == 0 && r == 0) {
        answer = max(answer, bfs());
        return;
    }
    for (int i = x; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (gaaaaarden[i][j] == 2 && (i > x || (i == x && j > y))) {
                if (g > 0) {
                    gaaaaarden[i][j] = 3;
                    comb(g - 1, r, i, j);
                }
                if (r > 0) {
                    gaaaaarden[i][j] = 4;
                    comb(g, r - 1, i, j);
                }
                gaaaaarden[i][j] = 2;
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> g >> r;
    for(int i = 1; i<=n; i++)
        for(int j = 1; j<=m; j++) cin >> gaaaaarden[i][j];
    
    comb(g,r,1,0); // 가능한 모든 배치 탐색 시작
    cout << answer;
}
