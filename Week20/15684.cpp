#include <iostream>
#include <vector>

using namespace std;

int n, m, h;
int min_cnt = 4;
bool visited[31][11];

bool check(){
    // 모든 세로선 i에 대해 출발해서
    for(int i = 1; i <= n; i++){
        int pos = i;
        // 위에서 아래로 사다리를 내려감
        for(int j = 1; j <= h; j++){
            if(visited[j][pos])        // 오른쪽으로 이동
                pos++;
            else if(visited[j][pos-1]) // 왼쪽으로 이동
                pos--;
        }
        // 출발한 세로선과 도착한 세로선이 다르면 실패
        if(pos != i) return false;
    }
    return true;
}

void dfs(int height, int cnt){
    // 이미 최소값보다 많이 추가했다면 중단
    if(cnt >= min_cnt) return;

    // 현재 상태가 성공이면 최소 개수 갱신
    if(check()) min_cnt = cnt;

    // height부터 끝까지 가로선 추가 시도
    for(int i = height; i <= h; i++){
        for(int j = 1; j < n; j++){
            // 이미 가로선이 있거나 인접한 가로선이 있으면 불가
            if(visited[i][j] || visited[i][j-1] || visited[i][j+1]) continue;
            visited[i][j] = true;
            dfs(i, cnt + 1);  
            visited[i][j] = false; // 원상 복구 (백트래킹)
        }
    }
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> h;
    for(int i = 0 ; i < m; i++){
        int x,y;
        cin >> x >> y;
        visited[x][y] = 1;
    }
    // 가로선 추가 탐색 시작
    dfs(1, 0);
    // 3개 초과 필요하면 불가능
    if(min_cnt > 3) cout << -1;
    else cout << min_cnt;
}