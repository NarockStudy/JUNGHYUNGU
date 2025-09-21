#include <iostream>
#include <queue>
#include <string>
using namespace std;

const int MAX = 1500;
int R, C;
char lake[MAX][MAX];
bool visited[MAX][MAX]; 
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};

queue<pair<int,int>> waterQ, waterNext; // 현재 물, 내일 물
queue<pair<int,int>> swanQ, swanNext;   // 현재 백조 이동, 내일 이동

pair<int,int> swans[2]; // 백조 위치 저장

// 하루가 지나면 얼음을 녹임
void melt(){
    while(!waterQ.empty()){
        auto [x,y] = waterQ.front(); waterQ.pop();
        for(int i=0;i<4;i++){
            int nx = x + dx[i], ny = y + dy[i];
            if(nx<0||ny<0||nx>=R||ny>=C) continue;
            if(lake[nx][ny] == 'X'){ 
                lake[nx][ny] = '.';        // 얼음이 물로 바뀜
                waterNext.push({nx,ny});   // 내일 물 후보
            }
        }
    }
}

// 다른 백조에게 도달할 수 있는지 확인
bool moveSwan(){
    while(!swanQ.empty()){
        auto [x,y] = swanQ.front(); swanQ.pop();
        for(int i=0;i<4;i++){
            int nx = x + dx[i], ny = y + dy[i];
            if(nx<0||ny<0||nx>=R||ny>=C) continue;
            if(visited[nx][ny]) continue;

            visited[nx][ny] = true;
            // 다른 백조 도착
            if(make_pair(nx,ny) == swans[1]) return true; 
            // 물은 즉시 이동
            if(lake[nx][ny] == '.') swanQ.push({nx,ny});   
            // 얼음은 내일 이동     
            else swanNext.push({nx,ny});                   
        }
    }
    return false;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> R >> C;
    int idx = 0;
    for(int i=0;i<R;i++){
        string row; cin >> row;
        for(int j=0;j<C;j++){
            lake[i][j] = row[j];
            if(lake[i][j] != 'X') waterQ.push({i,j}); // 초기 물 큐
            if(lake[i][j] == 'L') swans[idx++] = {i,j};
        }
    }

    swanQ.push(swans[0]);
    visited[swans[0].first][swans[0].second] = true;

    int days = 0;
    while(true){
        if(moveSwan()) break;  // 두 백조가 만나면 종료
        melt();                // 하루치 얼음 녹이기
        waterQ = waterNext;    // 내일 물 → 오늘 물
        swanQ = swanNext;      // 내일 백조 이동 → 오늘 이동
        while(!waterNext.empty()) waterNext.pop();
        while(!swanNext.empty()) swanNext.pop();
        days++;
    }

    cout << days;
}






/*
dfs + 시뮬 시간 초과남 
#include <iostream>
#include <vector>

using namespace std;

const int MAX = 1500;
bool meet; // 두 백조 만남?
int r,c;
int dx[] = {0,1,0,-1};
int dy[] = {-1,0,1,0};

vector <pair<int,int>> backs; // 2마리 백조 위치 저장
vector <pair<int,int>> melt; // 빙판
int lake[MAX + 10][MAX + 10]; // 호수상태
int visited[MAX + 10][MAX + 10];


// 현재 백조가 갈 수 있는 물 구역 탐색
// back = 1 이면, 도중에 다른 백조 위치에 도달했는지
void dfs(int y, int x, bool back){
    visited[y][x] = 1;
    for(int i = 0; i< 4; i++){
        int ny = y + dy[i];
        int nx = x + dx[i];
        if(ny < 0 || nx < 0 || ny >= r || nx >= c) continue;
        if(visited[ny][nx]) continue;

        if(lake[ny][nx] == '.'){
            // 물이면 dfs로 계속 이동ㄴ
            visited[ny][nx] = 1;
            dfs(ny,nx,back);
        }

        if(lake[ny][nx] == 'X'){
            // 빙판 만나서 오늘 못감, 내일 녹일 좌표 melt에 푸시
            visited[ny][nx] = 1;
            melt.push_back({ny,nx});
        }
        if(back && ny == backs[1].first && nx == backs[1].second){
            meet = true;
            return;
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int answer = 0;
    cin >> r >> c;
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            char ch;
            cin >> ch;
            lake[i][j] = ch;
            if(ch == 'L') backs.push_back({i,j});
        }
    }


    // 백조가 만날 때까지 반복
    while(!meet){
        dfs(backs[0].first, backs[0].second, true);
        if(meet) break; // 백조끼리 만나면 종료

        for(int i = 0 ; i < r; i++){
            for(int j = 0 ; j < c; j++){
                if(!visited[i][j] && lake[i][j] == '.'){
                    // visited[i][j] = 1;
                    dfs(i,j,0);
                }
            }
        }
        // 오늘 기록된 빙판 녹임
        for (auto i : melt) lake[i.first][i.second] = '.';
        
        answer++;
        fill(&visited[0][0], &visited[0][0] + 1510 * 1510, 0); // 방문 초기화
    }

    cout << answer;
    
}*/