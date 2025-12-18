#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n;

struct student {
    string name;
    int korean, english, math;
};

vector<student> v;

bool cmp(student &a, student &b){
    if(a.korean == b.korean){
        if(a.english == b.english){
            if(a.math == b.math) return a.name < b.name;
            return a.math > b.math;
        }
        return a.english < b.english;
    }
    return a.korean > b.korean;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 0 ; i < n; i++){
        string name;
        int korean, english, math;
        cin >> name >> korean >> english >> math;
        v.push_back({name, korean, english, math});
    }

    sort(v.begin(), v.end(), cmp);
    for(auto &a : v) cout << a.name << "\n";
}