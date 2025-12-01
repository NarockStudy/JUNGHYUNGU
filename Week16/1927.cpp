#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n;
// 최소 힙(오름차순 우선순위 큐) 선언
priority_queue<int, vector<int>, greater<int>> pq;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n; // 명령 개수 입력

    for(int i = 0 ; i < n ; i++){
        int x;
        cin >> x;

        if(x == 0){ 
            // 0이 들어오면 최소값 출력 요청
            if(pq.empty()){
                // 비어있으면 0 출력
                cout << "0" << "\n";
            }
            else {
                // 가장 작은 값 출력 후 제거
                cout << pq.top() << "\n";
                pq.pop();
            }
        }
        else {
            // 0이 아니면 힙에 값 삽입
            pq.push(x);
        }
    }
}
