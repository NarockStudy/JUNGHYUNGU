#include <iostream>
#include <string>
#include <deque>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    string strp, strn;
    int T, N;
    

    cin >> T;
    while(T--)
    {   
        cin>>strp>>N>>strn;
        deque <int> dq;
        // d = 방향 (true = 정방향, false = 역방향)
        // flag = 에러 발생 여부
        bool d = true; 
        bool flag = true;
        string temp = "";
        for(int i = 1;i<int(strn.size());i++)
        {
            // 괄호, 콤마 기준으로 숫자 추출해서 저장
            if(strn[i] ==',' || strn[i]==']'){
                if(temp!="")dq.push_back(stoi(temp));
                temp = "";
            }
            else temp += strn[i];
        }
        for(int  i = 0; i<int(strp.size());i++)
        {
            if(strp[i]=='R')
            {
                // R → 방향 뒤집기 (실제로 reverse하지 않고 flag만 토글)
                d = !d;
            }
            else if (strp[i]=='D')
            {
                // 현재 방향에 따라 앞/뒤에서 원소 제거
                if(dq.empty()) {
                    flag = false;
                    break;
                }
                else {
                    if(d) dq.pop_front();
                    else dq.pop_back();
                }
            }
        }
        if(!flag) cout << "error" << "\n";
        else{
            if(!d) reverse(dq.begin(), dq.end());
            cout<<"[";
            for(int i = 0; i<dq.size();i++)
            {
                if(i == int(dq.size()-1)) cout<<dq[i];
                else cout << dq[i] << ",";
            }
            cout<<"]" << "\n";
        }
    }


}