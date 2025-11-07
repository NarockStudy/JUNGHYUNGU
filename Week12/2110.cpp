#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

long long n,c;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> c;
    vector<long long> v(n);
    for(int i = 0; i <n;i++) cin >> v[i];

    sort(v.begin(), v.end());

    long long low = 1, high = v[n -1] - v[0], answer = 0;

    while(low <= high){
        long long mid = (low + high) / 2; // 후보 거리
        long long last = v[0];            // 첫 집에 공유기 설치
        int cnt = 1;                      // 설치한 공유기 수

        for(int i = 1; i< n;i++){
            if(v[i] - last >= mid){ // 이전 설치 위치와 거리 >= mid
                cnt++;
                last = v[i];
            }
        }

        if(cnt >= c){           // 충분히 설치 가능 → 거리 늘림
            answer = mid;
            low = mid+1;
        }
        else high = mid -1;     // 부족 → 거리 줄임
    }
    
    cout << answer;
}