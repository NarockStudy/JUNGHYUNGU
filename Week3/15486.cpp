#include <iostream>
#include <algorithm>
#define MAX 1500001
using namespace std;

int n;
pair<int, int> tp[MAX];
int dp[MAX];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> tp[i].first >> tp[i].second;
    }

    int current_max = 0;
    for (int i = 1; i <= n + 1; i++) {
        // i번째 날까지 얻을 수 있는 최대 수익 갱신
        // dp[i]는 i-1일까지의 최대 수익
        current_max = max(current_max, dp[i]);
        
        // i번째 날에 상담을 시작했을 때, 상담이 끝나는 날
        int end_day = i + tp[i].first;
        
        // 상담이 n+1일을 넘기지 않는 경우에만 계산
        if (end_day <= n + 1) {
            // end_day 시점의 최대 수익을 갱신
            // (i일 상담 시작 전까지의 최대 수익 + i일 상담 수익)과 
            // end_day에 이미 계산된 값 중 더 큰 값으로 갱신
            dp[end_day] = max(dp[end_day], current_max + tp[i].second);
        }
    }
    cout << current_max;
    return 0;
}