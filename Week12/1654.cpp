#include <iostream>

using namespace std;

typedef long long ll;

int n,k;
int arr[10'005];

bool solve(ll x){
    ll cur = 0;
    for(int i = 0; i < k; i++) cur+= arr[i] / x;
    return cur>=n;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> k >> n;
    for (int i = 0; i< k; i++) cin>> arr[i];

    ll answer = 1;
    ll en = 0x7fffffff;
    while(answer < en){
        ll mid = (answer + en + 1) / 2;
        if(solve(mid)) answer = mid;
        else en = mid-1;
    }
    // mid 길이로 잘랐을 때 n개 이상이면 길이를 늘리고, 아니면 줄이는 이분 탐색 수행
    // 최종적으로 만들 수 있는 최대 랜선 길이(answer)를 출력
    cout << answer;
}
