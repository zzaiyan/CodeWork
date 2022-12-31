#include <bits/stdc++.h>
using namespace std;

auto eles = 5; // 每行元素个数

int main() {
  ifstream ifs("C:\\Users\\1\\Desktop\\t.txt", ios::in);
  ofstream ofs("C:\\Users\\1\\Desktop\\out.csv", ios::out);

  if (!ifs || !ofs)
    cerr << "file open error!\n";

  string buf;
  int cnt = 0;

  while (ifs >> buf) {
    ofs << buf;
    if (++cnt == eles) {
      ofs << endl;
      cnt = 0;
    } else {
      ofs << ",";
    }
  }

  cout << "Finished!\n";

  ifs.close();
  ofs.close();
}