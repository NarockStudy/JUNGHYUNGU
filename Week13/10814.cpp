#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool compare(pair<int,string> a, pair<int,string> b)
{
    return a.first < b.first;
}

int main()
{
    int n;
    cin >> n;
    vector<pair<int,string>> v(n);

    for(int i = 0; i < n; i++) cin >> v[i].first >> v[i].second;

    stable_sort(v.begin(), v.end(), compare);

    for(int i = 0; i < n; i++) cout << v[i].first << " " << v[i].second << "\n";

    // 나이순(오름차순)으로 회원 정보를 stable_sort로 정렬 (가입 순서 보존)
    // 정렬된 회원의 나이와 이름을 출력
}