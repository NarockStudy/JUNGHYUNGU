#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int n,l;
vector<pair<int,int>> v;
deque<pair<int,int>> dq;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> l;
    for(int i = 0; i < n; i++){
        int d;
        cin >> d;
        v.push_back(make_pair(d,i));
    }
    for(int i = 0; i<n; i++){
        //  dq의 뒷부분 값이 현재 값보다 크면 의미 없으므로 제거
        //    작은 값이 최소 후보가 되기 때문에, 큰 값은 뒤에 있어도 쓸모 없음
        while(!dq.empty() && dq.back().first > v[i].first) dq.pop_back();
        //  윈도우 범위에서 벗어난 원소 제거 현재 인덱스 i에서 l만큼 벗어나면 삭제
        while(!dq.empty() && dq.front().second <= i-l) dq.pop_front();
        dq.push_back(v[i]); 
        // 현재 윈도우에서의 최소값은 항상 덱의 맨 앞 원소
        cout << dq.front().first << " ";
    }
    
}