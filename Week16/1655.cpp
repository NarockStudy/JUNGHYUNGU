#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int n;

// mx: 최대 힙 (왼쪽 절반 저장, 중앙값은 여기 top에 위치)
// mn: 최소 힙 (오른쪽 절반 저장)
priority_queue<int, vector<int>, greater<int>> mn;
priority_queue<int> mx;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for(int i = 0 ; i < n; i++){
        int a;
        cin >> a;

        // 힙 크기를 통해 균형 맞추기
        // 1) 처음엔 mx가 비어 있으므로 mx에 넣는다.
        // 2) 두 힙의 크기가 같으면 mx에 넣는다. (중앙값이 mx에 있어야 함)
        // 3) mx가 더 많으면 mn에 넣는다.
        if(mx.empty()) mx.push(a);
        else if(mx.size() == mn.size()) mx.push(a);
        else mn.push(a);

        // 두 힙의 정렬 조건 유지:
        // 최대 힙(mx)의 모든 값 ≤ 최소 힙(mn)의 모든 값 이어야 함
        // 만약 mx.top() > mn.top() 이면 둘 교환
        if(!mn.empty() && !mx.empty() && (mx.top() > mn.top())){
            int max_val = mx.top(); mx.pop();
            int min_val = mn.top(); mn.pop();

            // 힙 조건에 맞게 swap
            mx.push(min_val);
            mn.push(max_val);
        }

        // 중앙값 출력 → 최대 힙의 top
        cout << mx.top() << "\n";
    }
}
