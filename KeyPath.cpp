#include <cstring>
#include <iostream>
using namespace std;
#define N 13
int main() {
  int map[N][N]; //邻接矩阵
  // 初始化矩阵的值全部为0表示各个顶点间没有边连接
  for (int i = 0; i <= N - 1; i++) {
    for (int j = 0; j <= N - 1; j++) {
      map[i][j] = -1;
    }
  }

  int a, b, values; //定义a,b，用来输入,values存储权值
  int v, l;         //顶点数和边数

  cout << "请输入顶点数：";
  cin >> v;
  cout << "请输入边数：";
  cin >> l;
  cout << "请输入边：" << endl;

  for (int i = 1; i <= l; i++) {
    cin >> a >> b >> values;
    map[a][b] = values; // 表示顶点a指向顶点b的边,且权值为values
  }

  int k;                     //用于计算度数
  int ID[N], OD[N];          //储存各顶点的入度和出度
  int ve[N], vl[N];          //顺拓扑序列取大，逆拓扑序列取小
  memset(ve, 0, sizeof(ve)); //初始化ve数组全为0

  for (int i = 1; i <= v; i++) { // 计算入度
    k = 0;
    for (int j = 1; j <= v; j++) {
      if (map[j][i] != -1) //如果顶点j到顶点i有边，则顶点i的入度+1
        k++;
    }
    ID[i] = k;
  }
  for (int i = 1; i <= v; i++) { //顺拓扑序列
    if (ID[i] == 0) {
      for (int j = 1; j <= v; j++) {
        if (map[i][j] !=
            -1) { //如果顶点j与顶点i有边，则删除这条边，并且顶点j的入度-1
          if (ve[j] < map[i][j] + ve[i]) //取大值
            ve[j] = map[i][j] + ve[i];
          ID[j]--;
        }
      }
    }
  }
  for (int i = 1; i <= v; i++) { // 计算出度
    k = 0;
    for (int j = 1; j <= v; j++) {
      if (map[i][j] != -1)
        k++;
    }
    OD[i] = k;
  }

  k = v;
  for (int i = 1; i <= v; i++) //将 vl 数组全部初始化为ve最后一顶点的值
    vl[i] = ve[k];

  for (int i = k; i >= 1; i--) { //逆拓扑序列
    if (OD[i] == 0) {
      for (int j = 1; j <= v; j++) {
        if (map[j][i] != -1) {
          if (vl[j] > vl[i] - map[j][i]) //取小值
            vl[j] = vl[i] - map[j][i];
          OD[j]--;
        }
      }
    }
  }
  cout << "****************************\n";
  cout << "Ve数组：";
  for (int i = 1; i <= k; i++) {
    cout << ve[i] << " ";
  }
  cout << endl;
  cout << "Ve数组：";
  for (int i = 1; i <= k; i++) {
    cout << vl[i] << " ";
  }
  cout << "\n****************************\n";

  cout << "关键路径：";
  for (int i = 1; i <= k - 1; i++) {
    if (ve[i] == vl[i]) {
      cout << i << "->";
    }
  }

  cout << k << endl;
  return 0;
}
