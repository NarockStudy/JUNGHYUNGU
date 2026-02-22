#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue> 

using namespace std;

int n, m;
int lab[50][50];
int visited[50][50];

int emptyCnt = 0;        // 퍼뜨려야 할 0의 개수
int answer = 2500;       // 최소 시간

int dx[4] = {0,-1,0,1};
int dy[4] = {1,0,-1,0};

bool selected[10];       // 선택된 바이러스 체크
vector<pair<int,int>> virus;

// BFS
void bfs(int size){
    queue<pair<int,int>> q;
    memset(visited, -1, sizeof(visited));

    // 선택된 바이러스들 시작점
    for(int i = 0; i < size; i++){
        if(selected[i]){
            int x = virus[i].first;
            int y = virus[i].second;
            visited[x][y] = 0;
            q.push({x,y});
        }
    }

    int infected = 0;
    int maxTime = 0;

    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        if(visited[x][y] >= answer) return;

        for(int i=0; i<4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx<0 || nx>=n || ny<0 || ny>=n) continue;
            if(lab[nx][ny] == 1) continue;
            if(visited[nx][ny] != -1) continue;

            visited[nx][ny] = visited[x][y] + 1;
            q.push({nx,ny});

            // 빈칸일 때만 카운트
            if(lab[nx][ny] == 0){
                infected++;
                maxTime = visited[nx][ny];

                // 다 감염되면 바로 종료
                if(infected == emptyCnt){
                    answer = min(answer, maxTime);
                    return;
                }
            }
        }
    }
}

// 조합 선택
void selectVirus(int idx, int cnt, int size){
    if(cnt == m){
        bfs(size);
        return;
    }

    for(int i = idx; i < size; i++){
        selected[i] = true;
        selectVirus(i+1, cnt+1, size);
        selected[i] = false;
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;

    for(int i=0; i < n; i++){
        for(int j=0; j < n; j++){
            cin >> lab[i][j];
            if(lab[i][j]== 2)
                virus.push_back({i,j});
            else if(lab[i][j] == 0)
                emptyCnt++;
        }
    }

    // 빈칸이 아예 없으면 0
    if(emptyCnt == 0){
        cout << 0;
        return 0;
    }

    selectVirus(0, 0, virus.size());
    if(answer == 2500) cout << -1;
    else cout << answer;
}