#include <iostream>

using namespace std;

int n, count, child;          
int arr[1'000'005];          

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n; 

    for(int i = 0 ; i < n; i++){
        cin >> child;  

        // child 번호로 끝나는 "연속된 번호 수열"의 길이
        // = (child-1 번호로 끝나는 수열 길이) + 1
        arr[child] = arr[child - 1] + 1;

        // 가장 긴 연속 부분 수열 길이를 갱신
        count = max(count, arr[child]);
    }

    // 전체 아이 수 - 가장 긴 연속 수열 길이 = 최소 이동 횟수
    cout << n - count;
}
