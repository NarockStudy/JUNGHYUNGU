#include <iostream>
#include <stack>

using namespace std;

#define X first
#define Y second
int n;
stack<pair<int,int>>s;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    long long answer =0;
    cin >> n;
    while(n--){
        int h;
        cin >> h;
        int count = 1;
        while(!s.empty() && s.top().X <= h){
            answer += s.top().Y;
            if(s.top().X==h) count += s.top().Y;
            s.pop();
        }
        if(!s.empty()) answer++;
        s.push({h, count});
    }

    cout << answer;

}