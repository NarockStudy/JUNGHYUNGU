#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
char stars[3072][6144];

void printstars(int n, int x, int y)
{
    if(n==3){
        stars[x][y] = '*';
        stars[x+1][y-1] = '*';
        stars[x+1][y+1] = '*';
        stars[x+2][y] = '*';
        stars[x+2][y-1] = '*';
        stars[x+2][y-2] = '*';
        stars[x+2][y+1] = '*';
        stars[x+2][y+2] = '*';
    }
    else{
        int half = n/2;
        // 위쪽 삼각형
        printstars(half, x, y);
        // 아래 왼쪽 삼각형
        printstars(half, x + half, y - half);
        // 아래 오른쪽 삼각형
        printstars(half, x + half, y + half);
    }
}

int main()
{
    int N;
    cin>>N;
    memset(stars, ' ', sizeof(stars)); // 공백 초기화

    printstars(N, 0 , N-1);
    for(int i = 0; i< N;i++){
        for(int j = 0;j<2*N-1;j++) {cout << stars[i][j];}
        cout<<'\n';
    }
}