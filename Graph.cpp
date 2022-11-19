template <class T, class E> int Graphlnk<T, E>::InDegree(int v) {
  int cnt = 0; //计数器
  for (int i = 0; i < numVertices; i++)
    for (auto p = NodeTable[v].adj; p; p = p->link)
      if (p->desk == v) {
        cnt++;
        break;
      }
  return cnt;
}

template <class T, class E> int Graphlnk<T, E>::OutDegree(int v) {
  int cnt = 0;
  for (auto p = NodeTable[v].adj; p; p = p->link)
    cnt++;
  return cnt;
}

//递归算法,使用visited[]和parent判断
//顶点v可达的子图(连通分量)中是否存在环
template <class T, class E>
bool Graphlnk<T, E>::DFS(int v, bool visited[], int parent) {
  visited[v] = true; //标记当前结点访问过
  //对当前顶点的所有邻接点进行迭代
  for (auto p = NodeTable[v].adj; p; p = p->link) {
    //如果一个邻接点没有被访问过,递归访问
    if (!visited[p->dest]) {
      if (DFS(p->dest, visited, v)) //发现存在环,返回true
        return true;                //及时退出
    } //这一邻接点不是DFS树上i的父结点,且已经被访问过,则存在环
    else if (p->dest != parent)
      return true; //返回true
  }
  return false;
}
//如果无向图中含有环,返回true,否则返回false
template <class T, class E> bool Graphlnk<T, E>::haveCycle() {
  //标记所有顶点为未访问
  bool visited[numVertices]{false};
  //对每个未访问过的顶点,调用isCyclicUtil判断环是否存在
  for (int u = 0; u < numVertices; ++u)
    if (!visited[u]) //不对已经访问过的顶点进行递归
      if (DFS(u, visited, -1))
        return true;
  return false;
}

//迭代算法,存在环时返回true
template <class T, class E> bool Graphlnk<T, E>::BFS(int v, bool visited[]) {
  //定义每个顶点的parent为-1
  int parent[numVertexes];
  for (int i = 0; i < numVertexes; ++i)
    parent[i] = -1;
  //定义一个BFS使用的queue
  queue<int> q;
  q.push(v);
  visited[v] = true;
  while (q.size()) {
    int u = q.front();
    q.pop();
    for (auto p = NodeTable[u].adj; p; p = p->link) {
      if (!visited[p->dest]) {   //如果没有访问
        visited[p->dest] = true; //标记访问
        q.push(p->dest);         //进队
        parent[p->dest] = u;     //记录它的parent
      } else if (p->dest != parent[u]) // v是u的邻接点,被访问过,但不是u的parent
        return true;                   //返回true
    }
  }
  return false;
}
template <class T, class E> bool Graphlnk<T, E>::haveCycle() {
  //标记所有顶点为未访问
  bool visited[numVertexes]{false};
  for (int i = 0; i < numVertexes; ++i)
    if (!visited[i] && BFS(i, visited))
      return true;
  return false;
}