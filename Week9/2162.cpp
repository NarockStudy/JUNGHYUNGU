#include <iostream>
#include <algorithm>

#define X first
#define Y second

using namespace std;

typedef pair<int, int> pi;


pair<int, int> a[3005], b[3005];
int line[3005], m_size[3005];
int n;

int find(int a) {
    if (a == line[a]) return a;
    return line[a] = find(line[a]); // 경로 압축
}

void Union(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return;
    line[b] = a;              // 같은 그룹으로 묶기
    m_size[a] += m_size[b];   // 그룹 크기 합산
    m_size[b] = 0;            // 병합된 그룹은 0으로 초기화
}

int ccw(pi a, pi b, pi c){
    int tmp = a.X * b.Y + b.X * c.Y + c.X * a.Y;
    tmp = tmp - (a.Y  * b.X + b.Y * c.X + c.Y * a.X);
    if(tmp < 0) return -1;
    if(tmp > 0) return 1;
    else return 0;
}

// 두 선분 (a,b)와 (c,d)가 교차하는지 판별
bool check(pi a, pi b, pi c, pi d) {
    int abc = ccw(a, b, c);
    int abd = ccw(a, b, d);
    int cda = ccw(c, d, a);
    int cdb = ccw(c, d, b);

    if (abc * abd == 0 && cda * cdb == 0) { // 일직선 상
        if (a > b) swap(a, b);
        if (c > d) swap(c, d);
        return a <= d && c <= b; // 좌표가 겹치는지 확인
    }
    return (abc * abd <= 0) && (cda * cdb <= 0);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].X >> a[i].Y >> b[i].X >> b[i].Y;
        line[i] = i;      // 초기에는 자기 자신이 루트
        m_size[i] = 1;    // 초기 그룹 크기 1
    }

    // 모든 선분 쌍에 대해 교차 여부 검사
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (check(a[i], b[i], a[j], b[j])) {
                Union(i, j);
            }
        }
    }

    int max_size = 0, g_num = 0;

    // 그룹 개수 및 최대 그룹 크기 계산
    for (int i = 1; i <= n; i++) {
        if (m_size[i] != 0) { // 루트 노드만 카운트
            g_num++;
            max_size = max(max_size, m_size[i]);
        }
    }

    cout << g_num << " " << max_size;
}