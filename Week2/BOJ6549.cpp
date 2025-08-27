#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

int n;
long long hist[1'000'005];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(1){
        long long answer = 0;
        stack<int> s;
        cin >> n;
        if(n == 0) break;
        for(int i = 0; i<n; i++) cin >> hist[i];
        hist[n] = -1; // 마지막에 모든 막대를 비우기 위한 '센티넬 값'

        for(int j = 0; j <=n; j++){
            // 현재 막대 높이(hist[j])가 스택의 top에 해당하는 막대보다 작다면
            // 스택을 pop하면서 직사각형 넓이를 계산
            while(!s.empty() && hist[j] < hist[s.top()]) {
                int h,w;
                h = s.top(); s.pop();
                
                if(s.empty()) w = j; 
                else w = j - s.top() -1;

                answer = max(answer, hist[h] * w);
            }
            s.push(j);
        }
        
        cout << answer << "\n";
        
    }
}