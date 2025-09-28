#include <iostream>
using namespace std;

// (i, j) 좌표가 별인지 공백인지 판단해서 출력하는 재귀 함수
void star(int i, int j, int n)
{
    // 현재 블록이 3x3 중간(공백 영역)에 해당하면 공백 출력
    if((i/n)%3==1 && (j/n)%3==1)
    {
        cout << " ";
    }
    else
    {
        if(n==1) 
        {
            cout << "*"; // 더 이상 쪼갤 수 없는 크기면 별 출력
        }
        else 
        {
            star(i, j, n/3); // 더 작은 블록으로 나누어 재귀 호출
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n; // 패턴 크기 입력 (3^k)

    // n x n 전체 좌표 순회
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            star(i, j, n); // 각 좌표에 맞는 문자 출력
        }
        cout << "\n"; // 줄바꿈
    }
}
