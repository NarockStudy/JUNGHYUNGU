#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int n, w, l;        // n = 트럭 수, w = 다리 길이, l = 최대 하중
int arr[1005];      // 트럭 무게 저장 배열

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> w >> l;
    for(int i = 0; i < n; i++) cin >> arr[i];

    int time = 0;       
    int total = 0;      
    queue<int> q;       

    for(int i = 0; i < n; i++){
        while (1) {
            // 다리가 꽉 찼으면 가장 오래된 칸 pop (한 칸 전진)
            if(q.size() == w){
                total -= q.front();
                q.pop();
            }

            // 현재 트럭(arr[i])이 올라갈 수 있으면 break로 나가서 push
            if(total + arr[i] <= l) break;

            //무게 초과라면 트럭을 못 올리고 0을 넣어서 시간만 흐르게 함
            q.push(0);
            time++;
        }

        // 트럭을 다리에 올림
        q.push(arr[i]);
        total += arr[i];
        time++;
    }

    // 마지막 트럭이 다리를 완전히 건너는 시간 w 더해줌
    cout << time + w;
}
