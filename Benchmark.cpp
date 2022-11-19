#include <bits/stdc++.h>
const int N_qsort = 30000;         //快排的数据规模
const double M = 60000, N = 60000; //整点、浮点运算的规模
const int N_pi = 100000000;        //计算圆周率的运算规模
double s_int, s_float, s_pi, s_sort;
void int_comp(void);                    //整点运算
void float_comp(void);                  //浮点运算
void pi_comp(void);                     //泰勒级数推论式计算圆周率
void Qsort(int a[], int low, int high); //快排算法
void qsort(void);                       //调用快排算法的函数
void panduan();

int main() {
  printf("------\n性能测试开始\n");
  int_comp();   //整点运算
  float_comp(); //浮点运算
  pi_comp();    //泰勒级数推论式计算圆周率
  qsort();      //快速排序
  printf("------\n测试结束\n");
  printf("整点运算得分:%lf\n", s_int);
  printf("泰勒级数推论式计算圆周率运算得分:%lf\n", s_pi);
  printf("排序运算得分:%lf\n", s_sort);
  printf("总得分:%lf\n", s_int + s_float + s_pi + s_sort);
  panduan();
  return 0;
}

void int_comp(void) { //整点加法
  printf("整点运算测试中(运算次数为:%lf)\n", (double)M * N);
  clock_t start, end;
  int i, j;
  start = clock();
  for (i = 0; i < M; i++)
    for (j = 0; j < N; j++)
      ;
  end = clock();
  double duration = (double)(end - start) / CLOCKS_PER_SEC;
  double score = (M * N) / duration;
  /*注：score本身即为运算速度，数量级一般在亿，为方便起见，本程序的分数均采用运算速度除以一万后的结果！除特殊说明，后面类同！*/
  s_int = score / 10000;
  // printf("整点运算测试完毕!分数:%lf\n",s_int);
}

void float_comp(void) { //浮点加法
  printf("浮点运算测试中(运算次数为:%lf)\n", (double)M * N);
  clock_t start, end;
  double i, j;
  start = clock();
  for (i = 0; i < M; i++)
    for (j = 0; j < N; j++)
      ;
  end = clock();
  double duration = (double)(end - start) / CLOCKS_PER_SEC;
  double score = (M * N) / duration;
  s_float = score / 10000;
  // printf("浮点运算测试完毕!分数:%lf\n",s_float);
}

void pi_comp(void) {
  printf("泰勒级数推论式计算圆周率中(运算次数为:%d)\n", N_pi);
  int m, i = 1;
  double s = 0;
  clock_t start, end;
  start = clock();
  for (m = 1; m < N_pi; m += 2) {
    s += i * (1.0 / m);
    i = -i;
  }
  end = clock();
  double duration = (double)(end - start) / CLOCKS_PER_SEC;
  double score = N_pi / duration;
  //下面一行可输出计算出来的圆周率
  printf("pi=%lf\n", 4 * s);
  s_pi = score / 10000;
  // printf("泰勒级数推论式计算圆周率完毕!分数:%lf\n",s_pi);
}
void Qsort(int a[], int low, int high) { //快排算法
  if (low >= high)
    return;
  int first = low;
  int last = high;
  int key = a[first];
  while (first < last) {
    while (first < last && a[last] >= key)
      --last;
    a[first] = a[last];
    while (first < last && a[first] <= key)
      ++first;
    a[last] = a[first];
  }
  a[first] = key;
  Qsort(a, low, first - 1);
  Qsort(a, first + 1, high);
}
void qsort(void) { //调用快排算法的函数
  int a[N_qsort], i;
  for (i = N_qsort; i > 0; i--)
    a[N_qsort - 1] = i;
  printf("排序运算中(对%d个数进行快速排序)\n", N_qsort); //采用最坏时间方案
  clock_t start, end;
  start = clock();
  Qsort(a, 0, N_qsort - 1);
  end = clock();
  double duration = (double)(end - start) / CLOCKS_PER_SEC;
  double score = (N_qsort * N_qsort) / duration;
  s_sort = score / 10000;
  // printf("排序运算测试完毕!分数:%lf\n",s_sort);
}
void panduan() {
  double i = s_int + s_float + s_pi + s_sort;
  printf("根据分数，授予您的爱机<");
  if (i > 0 && i <= 50000) {
    printf("渣渣");
  } else if (i >= 50000 && i < 80000) {
    printf("低端");
  } else if (i >= 80000 && i < 200000) {
    printf("中端");
  } else if (i >= 200000 && i < 350000) {
    printf("高端");
  } else if (i >= 350000 && i < 500000) {
    printf("超高端");
  } else if (i >= 500000) {
    printf("机皇");
  }
  printf(">称号\n");
}
