#include <bits/stdc++.h>
using namespace std;

auto eles = 16; // 每行元素个数

int main() {
  ifstream ifs("C:\\Users\\1\\Desktop\\in.txt", ios::in);
  ofstream ofs("C:\\Users\\1\\Desktop\\out.txt", ios::out);

  if (!ifs || !ofs)
    cerr << "file open error!\n";

  string buf;
  int cnt = 0;

  while (ifs >> buf) {
    if (cnt == 4)
      buf = "0";
    ofs << buf;
    if (++cnt == eles) {
      ofs << endl;
      cnt = 0;
    } else {
      ofs << "\t";
    }
  }

  cout << "Finished!\n";

  ifs.close();
  ofs.close();
}