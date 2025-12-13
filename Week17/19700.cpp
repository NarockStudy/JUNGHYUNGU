#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

pair<int, int> a[500'005];   
multiset<int> ms;          
int n;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for(int i = 0; i < n; i++) 
        cin >> a[i].first >> a[i].second;

    
    sort(a, a+n, greater<pair<int,int>>());

    for(int i = 0; i < n; i++){
        // 현재 학생(k명 이하 조건)을 수용할 수 있는 수업 탐색
        auto it = ms.lower_bound(-a[i].second + 1);

        if(it == ms.end()){
            // 들어갈 수 있는 수업이 없으면 새 수업 생성
            ms.insert(-1);
        } else {
            // 해당 수업에 학생 추가
            ms.erase(it);
            ms.insert(*it - 1);
        }
    }

// 필요한 최소 수업 개수
cout << ms.size();
}
