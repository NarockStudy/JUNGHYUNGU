#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

#define MAX 8
#define X first
#define Y second

using namespace std;

int n, m, answer = -1;
int arr[MAX][MAX], temp[MAX][MAX], visited[MAX][MAX];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

vector<pair<int,int>> virus;  
vector<pair<int,int>> house;  

/**
 * @brief BFS를 이용해 바이러스 확산 시뮬레이션
 * temp 배열에 감염을 퍼뜨리고 visited로 방문 체크
 */
void bfs(int x, int y){
    queue<pair<int, int>> q;
    q.push({x, y});
    visited[x][y] = 1;

    while(!q.empty()){
        int x = q.front().X;
        int y = q.front().Y;
        q.pop();

        for(int i = 0; i < 4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];

            // 경계 밖, 이미 방문한 곳은 제외
            if(nx < 0 || ny < 0 || nx >= n || ny >= m || visited[nx][ny]) continue;
            // 벽이거나 이미 감염된 곳 제외
            if(temp[nx][ny]) continue;

            visited[nx][ny] = 1;
            temp[nx][ny] = 2;  // 감염 표시
            q.push({nx, ny});
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> arr[i][j];
            if(arr[i][j] == 2) virus.push_back({i, j});   
            else if(arr[i][j] == 0) house.push_back({i, j}); 
        }
    }

    // 조합을 위한 boolean 벡터 (빈 칸 중 3개를 선택)
    vector<bool> index(house.size(), false);
    fill(index.end() - 3, index.end(), true);  // 마지막 3칸을 true로 설정 (3개 선택 조합 시작)

    do{
        int count = 0;

        // 원본 배열 복사 후 시뮬레이션용 temp 초기화
        memcpy(temp, arr, sizeof(arr));
        memset(visited, 0, sizeof(visited));

        // 선택된 3개의 빈 칸에 벽 세우기
        for(int i = 0; i < index.size(); i++){
            if(index[i])
                temp[house[i].X][house[i].Y] = 1;
        }

        // 모든 바이러스에 대해 BFS 확산
        for(auto &v : virus){
            bfs(v.X, v.Y);
        }

        // 감염되지 않은 안전 영역 카운트
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(temp[i][j] == 0)
                    count++;
            }
        }

        // 최대 안전영역 갱신
        answer = max(answer, count);

    } while(next_permutation(index.begin(), index.end()));  // 3개 벽 조합 반복

    cout << answer;
}
