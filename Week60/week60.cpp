
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int n;
string records;

int main() {
    cin >> n >> records;

    // 괄호 개수가 같으려면 전체 길이는 짝수여야 함
    if (n % 2 != 0) {
        cout << "No";
        return 0;
    }

    int low = 0, high = 0;

    for (char c : records) {
        if (c == '(') {
            low++;
            high++;
        }
        else if (c == ')') {
            low--;
            high--;
        }
        else {
            // '?'를 ')'로 보면 low 감소, '('로 보면 high 증가
            low--;
            high++;
        }

        // 최대한 '('로 처리해도 닫는 괄호가 더 많으면 불가능
        if (high < 0) {
            cout << "No";
            return 0;
        }

        // 열린 괄호 개수는 음수가 될 수 없으므로 0으로 보정
        low = max(0, low);
    }

    // 열린 괄호가 0개가 되는 경우가 존재하면 정상
    cout << (low == 0 ? "Yes" : "No");

    return 0;
}
