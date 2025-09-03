#include <iostream>
#include <vector>

using namespace std;

int n,k;

int main(){
    ios::sync_with_stdio(0);
    cin >> n >> k;
    vector<int> arr(n);
    vector<int> dp(k+1);
    for(int i = 0; i < n; i++) cin >> arr[i];
    dp[0] = 1; // 동전선택 x
    for(int i = 0; i<n;i++)
        for(int j = arr[i]; j<=k;j++) dp[j] += dp[j-arr[i]]; // 점화식

    cout << dp[k];
}