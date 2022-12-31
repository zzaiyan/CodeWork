#include <bits/stdc++.h>
using namespace std;
int main() {
  string str;
  cin >> str;
  for (auto &ch : str) {
    if (ch == '，')
      ch = '，';
  }
  cout << str << endl;
}
