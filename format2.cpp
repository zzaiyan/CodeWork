#include <bits/stdc++.h>
using namespace std;

int main() {
  map<int, vector<int>> mp;
  int buf1, buf2;
  while (cin >> buf1 >> buf2) {
    if (buf1 != -1)
      mp[buf1].push_back(buf2);
    else
      break;
  }
  for (auto &[a, b] : mp) {
    cout << "阿姨 " << a << " : ";
    for (auto &i : b) {
      cout << i;
      if (i != b.back())
        cout << " -> ";
    }
    cout << endl;
  }
  cin >> buf1;
}
