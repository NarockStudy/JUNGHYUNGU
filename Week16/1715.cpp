#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n, x;
// 가장 작은 값 두 개를 뽑기 위해 최소 힙 사용
priority_queue<int, vector<int>, greater<int>> pq;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    int answer = 0;
    
    // 1개일때 예외 처리
    if(n == 1) {cout << 0; return 0;}

    // 입력된 카드 묶음 크기를 최소 힙에 모두 넣음
    for(int i = 0 ; i < n; i++){
        cin >> x;
        pq.push(x);
    }

    // 힙이 빌 때까지 반복
    while(!pq.empty()){
        int sum = 0;

        // 가장 작은 카드 묶음 하나 꺼냄
        sum += pq.top();
        pq.pop();

        // 두 번째 카드 묶음이 있다면 꺼냄
        if(!pq.empty()){
            sum += pq.top();
            pq.pop();

            // 두 묶음을 합친 결과를 다시 힙에 넣음
            // 단, 마지막 합이라 힙이 비게 되면 넣지 않음
            if(!pq.empty()) 
                pq.push(sum);
        }

        // 합치는 데 필요한 비용을 누적
        answer += sum;
    }

    // 총 비용 출력
    cout << answer;
}
