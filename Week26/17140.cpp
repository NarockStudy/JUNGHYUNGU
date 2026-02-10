#include <bits/stdc++.h>
using namespace std;

int arr[101][101];
int cnt[101];
int r, c, k;

bool cmpPair(const pair<int,int>& a, const pair<int,int>& b) {
    // (숫자, 빈도) 기준: 빈도 오름차순 -> 숫자 오름차순
    if (a.second == b.second) return a.first < b.first;
    return a.second < b.second;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    
    cin >> r >> c >> k;
    r--; c--;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cin >> arr[i][j];

    int R = 3, C = 3;   // 현재 배열의 유효 행/열 크기
    int timeSec = 0;

    while (true) {
        if (r < R && c < C && arr[r][c] == k) break;
        if (timeSec == 100) { timeSec = -1; break; }

        bool rc_bool = (R >= C);  // true면 R연산(행 기준), false면 C연산(열 기준)

        int outerCount = rc_bool ? R : C;  // 처리할 "줄"의 개수 (행 개수 or 열 개수)
        int innerCount = rc_bool ? C : R;  // 한 줄에서 읽을 원소의 개수

        vector<int> v(outerCount, 0);
        int maxNewLen = 0;

        for (int line = 0; line < outerCount; line++) {
            fill(cnt, cnt + 101, 0);

            // 한 줄(행 또는 열)에서 빈도 카운트
            for (int idx = 0; idx < innerCount; idx++) {
                int val = rc_bool ? arr[line][idx] : arr[idx][line];
                if (val == 0) continue; // 0은 무시
                cnt[val]++;
            }

            // (숫자, 빈도)로 모으기
            vector<pair<int,int>> items;
            items.reserve(100);
            for (int val = 1; val <= 100; val++) {
                if (cnt[val] > 0) items.push_back({val, cnt[val]});
            }

            // 정렬: 빈도 오름차순 -> 숫자 오름차순
            sort(items.begin(), items.end(), cmpPair);

            // 결과 다시 쓰기
            int writePairs = min((int)items.size(), 50);

            for (int p = 0; p < writePairs; p++) {
                int number = items[p].first;
                int freq = items[p].second;

                if (rc_bool) {
                    arr[line][2*p] = number;
                    arr[line][2*p + 1] = freq;
                } else {
                    arr[2*p][line] = number;
                    arr[2*p + 1][line] = freq;
                }
            }

            int newLen = writePairs * 2;
            v[line] = newLen;
            maxNewLen = max(maxNewLen, newLen);

            // 이번 줄에서 남은 부분은 일단 나중에 0으로 채움
        }

        // 줄 길이를 maxNewLen에 맞추며 남은 칸 0 채우기
        for (int line = 0; line < outerCount; line++) {
            for (int idx = v[line]; idx < maxNewLen; idx++) {
                if (rc_bool) arr[line][idx] = 0;
                else arr[idx][line] = 0;
            }
        }

        // 7) R, C 업데이트
        if (rc_bool) C = maxNewLen;
        else R = maxNewLen;

        timeSec++;
    }

    cout << timeSec;
    return 0;
}