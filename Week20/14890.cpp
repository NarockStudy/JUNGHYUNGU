#include <iostream>
using namespace std;

int n, l;
int g1[105][105], g2[105][105];

// arr의 a번째 "줄(행)"이 경사로 규칙을 만족하는지 검사 (가능하면 1, 불가능하면 0)
int checked(int arr[105][105], int a){
    int visited[105][105] = {0,}; // 경사로가 이미 설치된 칸 표시(중복 설치 방지)

    int st = arr[a][0];           // 현재 기준 높이(이전 칸 높이)

    for(int i = 1; i < n; i++){
        // 높이가 같으면 그냥 진행
        if(arr[a][i] == st) continue;

        // [오르막] 현재 칸이 더 높아짐 (st -> st+1)
        if(arr[a][i] > st){
            st = arr[a][i]; // 새 기준 높이 갱신

            // 오르막은 "이전 l칸"이 모두 (st-1) 이어야 경사로 설치 가능
            for(int j = 1; j <= l; j++){
                int cur = i - j;               // 뒤로 l칸 확인
                if(cur < 0) return 0;          // 범위 밖이면 불가
                if(visited[a][cur]) return 0;  // 이미 경사로 설치된 칸이면 불가
                if(st - arr[a][cur] != 1) return 0; // 높이차가 정확히 1이 아니면 불가
                visited[a][cur] = 1;           // 경사로 설치 표시
            }
        }

        // [내리막] 현재 칸이 더 낮아짐 (st -> st-1)
        else if(arr[a][i] < st){
            // 내리막은 "앞으로 l칸"이 모두 (st-1) 이어야 경사로 설치 가능
            for(int j = 0; j < l; j++){
                if(i >= n) return 0;           // 앞으로 확인할 칸이 없으면 불가
                if(visited[a][i]) return 0;    // 이미 경사로 설치된 칸이면 불가
                if(st - arr[a][i] != 1) return 0; // 높이차가 정확히 1이 아니면 불가
                visited[a][i++] = 1;           // 경사로 설치 표시 + 다음 칸으로 이동
            }
            i--;                
            st = arr[a][i];     // 내리막 끝 지점의 높이를 새 기준으로 갱신
        }
    }

    return 1; // 끝까지 조건을 만족하면 통과
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> l;
    int answer = 0;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> g1[i][j];
            g2[j][i] = g1[i][j]; 
        }
    }

    for(int i = 0; i < n; i++){
        answer += checked(g1, i); 
        answer += checked(g2, i); 
    }

    cout << answer;
}
