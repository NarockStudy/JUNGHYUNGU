#include <iostream>
#include <vector>

int a[1005], d[1005], v[1005];

using namespace std;

// a[n]으로 끝나는 LIS의 길이를 계산하고, 경로를 v[]에 저장
int dp(int n){
    if(d[n]) return d[n];

    d[n] = 1;
    v[n] = 0;
    for(int i = 1; i < n; i++){
        // 앞에 더 작은 숫자 a[i]가 있고, 그 숫자를 잇는게 더 길어지면
        if (a[i] < a[n] && d[n] < dp(i) + 1){
            d[n] = dp(i) + 1; // 길이 갱신
            v[n] = i;         // a[i]가 a[n]의 바로 앞 숫자라고 기록
        }
    }
    return d[n];
}

// v[]에 기록된 경로를 따라가며 수열 출력
void print(int n){
    if(!v[n]){
        cout << a[n] << " ";
        return ;
    }
    print(v[n]);

    cout << a[n] << " ";
}

int main(){
    int n, index, answer = 0;
    cin >> n;
    for(int i = 1; i<=n; i++) cin >> a[i];
    // 모든 숫자에 대해 LIS 길이를 계산하며 전체 최댓값 찾기
    for(int i = 1; i<=n; i++){
        if(dp(i) > answer) {
            answer = dp(i);
            index = i; // 최장 길이일 때의 마지막 숫자 위치 저장
        }
    }

    cout << answer << "\n";
    print(index);

}