#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int n;
vector<int> v;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int x;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        v.push_back(x);
    }

    sort(v.begin(), v.end());

    for (int i = 0; i < v.size(); i++)
        cout << v[i] << "\n";

    // 입력받은 n개의 정수를 벡터에 저장
    // 오름차순으로 정렬 후 한 줄씩 출력
}
