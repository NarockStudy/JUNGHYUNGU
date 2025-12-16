#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int n,c;

map<int, pair<int,int>> m;
vector<pair<pair<int,int>, int>> v;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> c;

    for(int i = 0; i < n; i++){
        int num;
        cin >> num;
        // 숫자 등장 횟수를 음수로 누적하고, 처음 등장한 위치를 함께 저장
        if(m.count(num)) m[num].first--;
        else m.insert({num, {-1, i}});
    }

    for(auto &it : m){
        // (등장 횟수, 최초 등장 인덱스)를 정렬 기준으로 만들기
        v.push_back({it.second, it.first});
    }

    // 등장 횟수 ↓, 최초 등장 위치 ↑ 기준으로 정렬
    sort(v.begin(), v.end());

    for(auto &it : v){
        // 저장된 횟수만큼 해당 숫자 출력
        while(it.first.first++) cout << it.second << " ";
    }

}
