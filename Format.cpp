#include <bits/stdc++.h>
using namespace std;

auto eles = 6;

auto main() -> int {
  ifstream ifs("C:\\Users\\1\\Desktop\\in.txt", ios::in);
  ofstream ofs("C:\\Users\\1\\Desktop\\out.txt", ios::out);

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

  return 0;
}