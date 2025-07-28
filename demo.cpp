#include <bits/stdc++.h>
using namespace std;
void move(int &x, int &y, char &ch) {
    if(ch == 'U') y--;
    else if(ch == 'D') y++;
    else if(ch == 'R') x++;
    else x--;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s; cin >> s;
    int x = 0, y = 0;
    for(char &ch : s) move(x, y, ch);
    cout << x << " " << y;
    return 0;
}