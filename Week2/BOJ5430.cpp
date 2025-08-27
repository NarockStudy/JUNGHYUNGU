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
        bool d = true;
        bool flag = true;
        string temp = "";
        for(int i = 1;i<int(strn.size());i++)
        {
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
                d = !d;
            }
            else if (strp[i]=='D')
            {
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