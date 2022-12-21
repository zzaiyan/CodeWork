#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

//选出key
template <class K, class V> struct PairSelect1st {
  const K &operator()(const pair<K, V> &kv) { return kv.first; }
};
template <class K> struct KSelect1st {
  const K &operator()(const K &k) { return k; }
};

//转成整型
template <class K> struct HashFunc {
  size_t operator()(const K &val) { return val; }
};
//模板的特化
template <> struct HashFunc<std::string> {
  size_t operator()(const std::string &s1) {
    size_t sum = 0;
    for (size_t i = 0; i < s1.size(); i++) {
      sum = sum * 131 + s1[i];
    }

    return sum;
  }
};

//比较判断
template <class K> struct equal_to {
  bool operator()(const K &lval, const K &rval) { return lval == rval; }
};
template <>
//模板特化
struct equal_to<std::string> {
  bool operator()(const std::string &s1, const std::string &s2) {
    return s1 == s2;
  }
};

//素数表
const int PRIMECOUNT = 28;
const size_t primeList[PRIMECOUNT] = {
    53ul,         97ul,         193ul,       389ul,       769ul,
    1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
    49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
    1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
    50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
    1610612741ul, 3221225473ul, 4294967291ul};
namespace OpenHash {
template <class T> struct HashNode {
  typedef HashNode<T> Node;
  typedef HashNode<T> *pNode;

  HashNode<T> *_next;
  T _data;

public:
  HashNode(const T &data = T()) : _next(nullptr), _data(data) {}
};

template <class K, class V, class T, class Pred, class Select1st,
          class HashFunc>
class HashTable;

template <class K, class V, class T, class Ref, class Ptr, class Pred,
          class Select1st, class HashFunc>
struct Iterator {
  typedef HashNode<T> Node;
  typedef HashTable<K, V, T, Pred, Select1st, HashFunc> HashTable;
  typedef Iterator<K, V, T, Ref, Ptr, Pred, Select1st, HashFunc> self;

  Node *_pnode;
  HashTable *_pHT;

  Iterator(Node *pnode = nullptr, HashTable *pHT = nullptr)
      : _pnode(pnode), _pHT(pHT) {}

  Ref operator*() { return _pnode->_data; }
  const Ref operator*() const { return _pnode->_data; }
  Ptr operator->() { return &_pnode->_data; }
  const Ptr operator->() const { return &_pnode->_data; }

  self &operator++() {
    if (_pnode == nullptr)
      return *this;

    if (_pnode->_next != nullptr) {
      _pnode = _pnode->_next;
      return *this;
    }

    //_pnode->next == nullptr我们要去找现在的结点属于哪一个桶
    size_t index =
        HashFunc()(Select1st()(_pnode->_data)) % _pHT->_table.size() + 1;
    for (; index < _pHT->_table.size(); index++) {
      Node *cur = _pHT->_table[index];
      if (cur != nullptr) {
        _pnode = cur;
        return *this;
      }
    }
    _pnode = nullptr;
    return *this;
  }
  self operator++(int) {
    self tmp = *this;
    ++(*this);
    return tmp;
  }

  bool operator!=(const self &it) const { return _pnode != it._pnode; }
  bool operator==(const self &it) const { return _pnode == it._pnode; }
};

template <class K, class V, class T, class Pred = equal_to<std::string>,
          class Select1st = PairSelect1st<K, V>, class HashFunc = HashFunc<K>>
class HashTable {
  typedef HashNode<T> *pNode;
  typedef HashNode<T> Node;

  template <class K, class V, class T, class Ref, class Ptr, class Pred,
            class Select1st, class HashFunc>
  friend struct Iterator;

private:
  //存结点指针
  vector<pNode> _table;
  size_t _n;

public:
  typedef Iterator<K, V, T, const T &, const T *, Pred, Select1st, HashFunc>
      const_iterator;
  typedef Iterator<K, V, T, T &, T *, Pred, Select1st, HashFunc> iterator;

  HashTable() : _n(0) {}

  void clear() {
    for (size_t index = 0; index < _table.size(); index++) {
      pNode cur = _table[index];
      pNode prev = cur;
      while (cur) {
        prev = cur;
        cur = cur->_next;
        delete prev;
      }
    }
  }

  ~HashTable() { clear(); }

  iterator begin() {
    size_t index = 0;
    for (; index < _table.size(); index++) {
      pNode cur = _table[index];
      if (cur != nullptr)
        return iterator(cur, this);
    }
    return iterator(nullptr, this);
  }
  iterator end() { return iterator(nullptr, this); }

  const_iterator cbegin() {
    size_t index = 0;
    for (; index < _table.size(); index++) {
      pNode cur = _table[index];
      if (cur != nullptr)
        return const_iterator(cur, this);
    }
    return const_iterator(nullptr, this);
  }
  const_iterator cend() { return const_iterator(nullptr, this); }

  pair<iterator, bool> insert(const T &data) {
    //如果为空，则开空间
    if (!_table.size())
      _table.resize(53ul);
    //挑选key
    Select1st st1;
    //转换整型
    HashFunc hf;
    //判断是否冗余
    iterator ret = find(data);
    if (ret._pnode != nullptr)
      return std::make_pair(iterator(nullptr, this), false);

    //判断是否需要扩容
    if ((double)_n / (double)_table.size() >= 1) {
      vector<pNode> new_table(GetNextPrime(_table.size()));
      for (size_t i = 0; i < _table.size(); i++) {
        pNode cur = _table[i];
        if (cur != nullptr) {
          pNode next = _table[i];
          while (cur) {
            next = cur->_next;
            size_t new_index = (hf(st1(cur->_data))) % new_table.size();
            //头插
            cur->_next = new_table[new_index];
            new_table[new_index] = cur;
            cur = next;
          }
          _table[i] = nullptr;
        }
        //不推荐，插入的时候重新创建结点，浪费
        /*while(e != nullptr)
        {
                tmp.insert(e->_kv);
                e = e->_next;
        }*/
      }
      new_table.swap(_table);
    }

    //计算hashbucket的下标
    size_t index = hf(st1(data)) % _table.size();
    pNode newNode = new Node(data);
    //头插
    newNode->_next = _table[index];
    _table[index] = newNode;
    _n++;

    return std::make_pair(iterator(newNode, this), true);
  }

  iterator find(const T &data) {
    HashFunc hf;
    Select1st slt;
    if (_table.size() == 0)
      return iterator(nullptr, this);

    size_t index = hf(slt(data)) % _table.size();
    pNode cur = _table[index];
    while (cur) {
      if (Pred()(slt(cur->_data), slt(data)))
        return iterator(cur, this);
      else
        cur = cur->_next;
    }

    return iterator(nullptr, this);
  }

  bool erase(const T &data) {
    Select1st st1;
    size_t index = HashFunc()(st1(data)) % _table.size();
    pNode cur = _table[index];
    pNode prev = cur;
    while (cur) {
      if (Pred()(st1(cur->_data), st1(data))) {
        //找到了
        if (cur == _table[index]) //头结点
        {
          _table[index] = nullptr;
          _n--;
          delete cur;
          return true;
        } else {
          prev->_next = cur->_next;
          _n--;
          delete cur;
          return true;
        }
      } else //没找到
      {
        prev = cur;
        cur = cur->_next;
      }
    }
    return false;
  }

  size_t GetNextPrime(size_t prime) {
    size_t i = 0;
    for (; i < PRIMECOUNT; i++) {
      if (primeList[i] > primeList[prime])
        return primeList[i];
    }

    return primeList[i];
  }

  size_t size() const { return _n; }
};
} // namespace OpenHash

// OpenHash(开散列)
void Test_KV2() // KV模型
{
  OpenHash::HashTable<string, string, pair<string, string>> hts;

  pair<string, string> arr[] = {
      make_pair("left", "左边"),  make_pair("right", "右边"),
      make_pair("up", "向上"),    make_pair("down", "向下"),
      make_pair("left", "左边"),  make_pair("eat", "吃"),
      make_pair("sleep", "睡觉"), make_pair("run", "跑"),
      make_pair("jump", "跳")};

  for (auto e : arr)
    hts.insert(e);

  //非const迭代器
  OpenHash::HashTable<string, string, pair<string, string>>::iterator it =
      hts.begin();
  while (it != hts.end()) {
    cout << it->first << ":" << it->second << endl;
    it++;
  }
  cout << endl;

  hts.erase(make_pair("sleep", "睡觉"));
  hts.erase(make_pair("left", "左边"));
  hts.erase(make_pair("up", "向上"));

  // const类型
  OpenHash::HashTable<string, string, pair<string, string>>::const_iterator
      cit = hts.cbegin();
  while (cit != hts.cend()) {
    cout << cit->first << ":" << cit->second << endl;
    cit++;
  }
  cout << endl;
}

void Test_K2() // K模型
{
  OpenHash::HashTable<string, string, string, equal_to<string>,
                      KSelect1st<string>, HashFunc<string>>
      hts;
  string arr[] = {"left",  "左边", "right", "右边", "up",   "向上",
                  "down",  "向下", "left",  "左边", "eat",  "吃",
                  "sleep", "睡觉", "run",   "跑",   "jump", "跳"};
  for (auto e : arr)
    hts.insert(e);

  OpenHash::HashTable<string, string, string, equal_to<string>,
                      KSelect1st<string>, HashFunc<string>>::iterator it =
      hts.begin();
  while (it != hts.end()) {
    cout << *it << " ";
    it++;
  }
  cout << endl;
}

int main() {
  Test_KV2();
  return 0;
}