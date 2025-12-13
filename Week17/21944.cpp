#include <iostream>
#include <set>
using namespace std;

int N, M;
int probLevel[100'005]; 
int probAlg[100'005];   

set<int> lev_num[102];          
set<pair<int, int>> alg_num[102]; 
int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        int p, l, g;
        cin >> p >> l >> g;
        probLevel[p] = l;
        probAlg[p] = g;

        lev_num[l].insert(p);
        alg_num[g].insert(make_pair(l, p));
    }

    cin >> M;
    while (M--) {
        string cmd;
        cin >> cmd;
        if (cmd == "recommend") {
            int g, x;
            cin >> g >> x;

            if (x == 1) { // 알고리즘 G 중 가장 어려운 것+문제번호가 큰 것
                cout << (*(prev(alg_num[g].end()))).second << "\n";
            } else if (x == -1) { // 알고리즘 G 중 가장 쉬운 것+문제번호가 작은 것
                cout << (*(alg_num[g].begin())).second << "\n";
            }
        } else if (cmd == "recommend2") {
            int x;
            cin >> x;
            if (x == 1) { // 가장 어렵고 문제 번호가 큰 문제
                for (int i = 100; i >= 0; i--) {
                    if (lev_num[i].empty()) continue;

                    cout << *(--lev_num[i].end()) << "\n";
                    break;
                }
            } else { // x == -1
                for (int i = 1; i <= 100; i++) {
                    if (lev_num[i].empty()) continue;

                    cout << *(lev_num[i].begin()) << "\n";
                    break;
                }
            }
        } else if (cmd == "recommend3") {
            int x, l;
            cin >> x >> l;

            bool flag = true;
            if (x == 1) { // L이상 중 최소, 문제번호 작은 것
                for (int i = l; i <= 100; i++) {
                    if (lev_num[i].empty()) continue;
                    flag = false;
                    cout << *(lev_num[i].begin()) << "\n";
                    break;
                }
            } else { // L미만 중 가장 어려운 것, 최대
                for (int i = l - 1; i >= 0; i--) {
                    if (lev_num[i].empty()) continue;
                    flag = false;
                    cout << *(--lev_num[i].end()) << "\n";
                    break;
                }
            }
            if (flag)
                cout << -1 << "\n";
        } else if (cmd == "add") {
            int P, L, G;
            cin >> P >> L >> G;

            lev_num[probLevel[P]].erase(P);
            alg_num[probAlg[P]].erase({probLevel[P], P});

            probLevel[P] = L;
            probAlg[P] = G;
            lev_num[L].insert(P);
            alg_num[G].insert({L, P});
        } else if (cmd == "solved") {
            int P;
            cin >> P;

            lev_num[probLevel[P]].erase(P);
            alg_num[probAlg[P]].erase({probLevel[P], P});
            probLevel[P] = 0;
            probAlg[P] = 0;
        }
    }
}