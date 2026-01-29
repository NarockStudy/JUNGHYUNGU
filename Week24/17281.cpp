#include <iostream>
#include <algorithm>

using namespace std;

int s[50][9];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < 9; j++)
            cin >> s[i][j];

    int p[8] = {1,2,3,4,5,6,7,8};
    int ans = 0;

    do{
        // 타순 구성 (0번 선수 4번 타자 고정)
        int order[9];
        for(int i = 0; i < 3; i++) order[i] = p[i];
        order[3] = 0;
        for(int i = 3; i < 8; i++) order[i + 1] = p[i];

        int score = 0;
        int idx = 0; // 타자 인덱스

        for(int inning = 0; inning < n; inning++){
            int out = 0;
            int base[3] = {0,0,0}; // 1루, 2루, 3루

            while(out < 3){
                int cur = order[idx];
                idx = (idx + 1) % 9;

                int hit = s[inning][cur];

                if(hit == 0){
                    out++;
                } else {
                    // 주자 이동 (뒤에서부터)
                    for(int i = 2; i >= 0; i--){
                        if(base[i]){
                            if(i + hit >= 3) score++;
                            else base[i + hit] = 1;
                            base[i] = 0;
                        }
                    }
                    // 타자 진루
                    if(hit == 4) score++;
                    else base[hit - 1] = 1;
                }
            }
        }

        ans = max(ans, score);
    } while(next_permutation(p, p + 8));

    cout << ans;
}
