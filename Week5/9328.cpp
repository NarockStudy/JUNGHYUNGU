#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

#define X first
#define Y second

char board[105][105];
bool visited[105][105];
int dx[] = {-1, 0, 1, 0};
int dy[] = {0,-1, 0, 1};
int t;

bool is_upper(char c){ return ('A' <= c && c <= 'Z'); }
bool is_lower(char c){ return ('a' <= c && c <= 'z'); }

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> t;
    while(t--){
        int h, w;
        cin >> h >> w;

        // 보드 초기화 (외곽 + 내부)
        for(int i=0; i<105; i++) 
            for(int j=0; j<105; j++) 
                board[i][j] = '.';

        for(int i=1; i<=h; i++)
            for(int j=1; j<=w; j++)
                cin >> board[i][j];

        // 현재 가진 열쇠 저장
        vector<bool> has(26, false);
        string str; 
        cin >> str;
        if(str != "0"){
            for(char c : str) has[c-'a'] = true;
        }

        int ans = 0;

        // BFS 탐색
        queue<pair<int,int>> q;
        vector<vector<pair<int,int>>> door(26); // 각 문에서 대기하는 위치 저장
        memset(visited, 0, sizeof(visited));

        q.push({0,0});
        visited[0][0] = true;

        while(!q.empty()){
            auto [x,y] = q.front(); q.pop();

            for(int dir=0; dir<4; dir++){
                int nx = x + dx[dir], ny = y + dy[dir];
                if(nx < 0 || ny < 0 || nx > h+1 || ny > w+1) continue;
                if(visited[nx][ny]) continue;
                char cell = board[nx][ny];

                if(cell == '*') continue; // 벽

                // 문인데 열쇠가 없으면 door 큐에 넣고 continue
                if(is_upper(cell) && !has[cell-'A']){
                    door[cell-'A'].push_back({nx,ny});
                    continue;
                }

                visited[nx][ny] = true;

                if(cell == '$'){ 
                    ans++; // 문서 획득
                }
                else if(is_lower(cell)){ 
                    int k = cell - 'a';
                    if(!has[k]){ 
                        has[k] = true;
                        // 새 열쇠로 열 수 있는 문들을 큐에 다시 넣음
                        for(auto d : door[k]){
                            if(!visited[d.X][d.Y]){
                                q.push(d);
                                visited[d.X][d.Y] = true;
                            }
                        }
                        door[k].clear();
                    }
                }
                q.push({nx,ny});
            }
        }

        cout << ans << "\n";
    }
}
