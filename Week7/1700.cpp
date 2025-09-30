#include <iostream>

using namespace std;

int n, k;                
int schedule[105];      
int multitap[105];       
 
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int answer = 0;      

    cin >> n >> k;
    for(int i = 0; i < k; i++) cin >> schedule[i]; 
    
    // 스케줄대로 전기용품을 하나씩 확인
    for(int i = 0; i < k; i++){
        bool flag = 0;

        // 1. 이미 꽂혀 있는 경우 → 아무것도 안 함
        for(int j = 0; j < n; j++){
            if(multitap[j] == schedule[i]){
                flag = 1; 
                break;
            }
        }
        if(flag) continue;  // 이미 꽂혀 있으면 넘어감

        // 2. 빈 칸(=0)이 있으면 그 자리에 꽂음
        for(int j = 0; j < n; j++){
            if(multitap[j] == 0){
                multitap[j] = schedule[i];
                flag = 1;
                break;
            }
        }
        if(flag) continue;  // 빈 칸에 꽂았으면 넘어감

        // 3. 빈 칸도 없고, 이미 꽂혀 있지도 않은 경우 → 하나를 빼야 함
        int index = -1, last = -1; 
        // index: 뺄 자리, last: 가장 나중에 다시 사용되는 시점

        for(int j = 0; j < n; j++){   // 현재 꽂혀 있는 전기용품 각각 확인
            int temp = 0;

            // 앞으로의 스케줄에서 언제 다시 사용되는지 탐색
            for(int t = i+1; t < k; t++){
                if(schedule[t] == multitap[j]) break; // 다시 사용 시점 찾음
                temp++;  // 사용 전까지 지나가는 횟수 카운트
            }

            // 가장 나중에 쓰이거나, 아예 안 쓰이는 전기용품을 선택
            if(temp > last){
                last = temp;
                index = j;
            }
        }

        // 선택된 전기용품을 빼고 현재 전기용품 꽂기
        multitap[index] = schedule[i];
        answer++;   
    }

    cout << answer; 
}
