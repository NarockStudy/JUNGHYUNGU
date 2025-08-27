#include <iostream>
#include <stack>
using namespace std;

int n;
stack<int> s;
int answer[1'000'001];
int num[1'000'001];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i = 0; i < n; i++){
        cin >> num[i];
    }

    for(int i = n-1; i>=0; i--){
        while(!s.empty() && s.top() <= num[i]) s.pop();
        
        if(s.empty()) answer[i] = -1;
        else answer[i] = s.top();

        s.push(num[i]);
    }

    for(int i = 0; i < n; i++) cout << answer[i] << " ";
    

}