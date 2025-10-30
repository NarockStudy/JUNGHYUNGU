#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int t,n,k,w;
vector<int> d;
vector<vector<int>> v;
vector<int> dp;
vector<int> indegree;

void BFS(){
    queue<int> q;
    for(int i = 1; i<=n; i++){
        if(indegree[i]==0){
            q.push(i);
            dp[i] = d[i];
        }
    }
    while(!q.empty()){
        int curr = q.front(); q.pop();
        for(int i = 0 ; i < v[curr].size();i++){
            int next = v[curr][i];
            if(next > 0){
               dp[next] = max(dp[next], dp[curr] + d[next]);
               if(--indegree[next] == 0){ // 진입할 수 있는 간선이 하나뿐인 건물
                q.push(next);
               } 
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> t;
    for(int i = 0; i< t; i++){
        cin >> n >> k;
        d.resize(n+1);
        dp.resize(n+1);
        indegree.resize(n+1);
        v.resize(n+1);
        for(int j = 1; j<=n; j++) cin >> d[j];
        for(int l = 1; l <=k; l++){
            int x,y;
            cin >> x >> y;
            v[x].push_back(y);
            indegree[y]++;
        }
        cin >> w;
        BFS();
        cout << dp[w] << "\n";
        d.clear();
        dp.clear();
        indegree.clear();
        v.clear();
    }

    return 0;

}