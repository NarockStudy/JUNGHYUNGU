#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int t, n, m;
vector<int> a, b;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> t;   

    for(int i = 0; i < t; i++){
        cin >> n >> m;  
        a = vector<int>(n); 
        b = vector<int>(m);

       
        for(int i = 0; i < n; i++) cin >> a[i];
        
        for(int i = 0; i < m; i++) cin >> b[i];

        // 두 배열 모두 정렬
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        int answer = 0;

        // A의 원소마다 B에서 "자신보다 작은 원소 개수"를 구함
        for(int i = 0; i < n; i++){
            // upper_bound: (a[i] - 1)보다 큰 첫 위치 반환
            // 즉, b에서 (a[i] - 1) 이하 원소 개수 = 잡아먹을 수 있는 개수
            answer += upper_bound(b.begin(), b.end(), a[i] - 1) - b.begin();
        }

        cout << answer ;
    }
}
