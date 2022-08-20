#include "bits/stdc++.h"
using namespace std;
int dfs_time = 0;
int no_biconnected_components = 0;
int no_of_vertex = 0;
int no_of_edges = 0;
vector<int> low, parent, discovery_time;
vector<bool> visited;
vector<vector<int>> adjacency_list;
stack<pair<int, int>> stack1;
set<int> set1;
void DFS(int vertex)
{
  discovery_time[vertex] = dfs_time + 1;
  low[vertex] = dfs_time + 1;
  dfs_time = dfs_time + 1;
  visited[vertex] = true;
  int child = 0;
  for (int i = 0; i < adjacency_list[vertex].size(); i++)
  {
    int child_vertex = adjacency_list[vertex][i];
    if (visited[child_vertex] == false)
    {
      child = child + 1;
      stack1.push(make_pair(vertex, child_vertex));
      parent[child_vertex] = vertex;
      DFS(child_vertex);
      low[vertex] = min(low[vertex], low[child_vertex]);
      if (parent[vertex] == -1 && child > 1)
      {
        no_biconnected_components = no_biconnected_components + 1;
        cout << "biconnected_component_no: " << no_biconnected_components << '\n';
        pair<int, int> temp_pair = make_pair(vertex, child_vertex);
        while (stack1.top() != temp_pair)
        {
         // cout << stack1.top().first << " " << stack1.top().second << '\n';
          set1.insert(stack1.top().first);
          set1.insert(stack1.top().second);
          stack1.pop();
        }
        //cout << stack1.top().first << " " << stack1.top().second << '\n';
        set1.insert(stack1.top().first);
        set1.insert(stack1.top().second);
        stack1.pop();
        for(auto itr : set1)
        {
          cout << itr << ' ';
        }
        cout << '\n';
        set1.clear();
      }
      if (parent[vertex] != -1 && low[child_vertex] >= discovery_time[vertex])
      {
        no_biconnected_components = no_biconnected_components + 1;
        cout << "biconnected_component_no: " << no_biconnected_components << '\n';
        pair<int, int> temp_pair = make_pair(vertex, child_vertex);
        while (stack1.top() != temp_pair)
        {
          // cout << stack1.top().first << " " << stack1.top().second << '\n';
          set1.insert(stack1.top().first);
          set1.insert(stack1.top().second);
          stack1.pop();
        }
        // cout << stack1.top().first << " " << stack1.top().second << '\n';
        set1.insert(stack1.top().first);
        set1.insert(stack1.top().second);
        stack1.pop();
        for(auto itr : set1)
        {
          cout << itr << ' ';
        }
        cout << '\n';
        set1.clear();
      }
    }
    else if (parent[vertex] != child_vertex && discovery_time[child_vertex] < low[vertex])
    {
      low[vertex] = discovery_time[child_vertex];
      stack1.push(make_pair(vertex, child_vertex));
    }
  }
  return;
}

void biconnected_components()
{
  for (int i = 1; i <= no_of_vertex; i++)
  {
    if (visited[i] == false)
    {
      DFS(i);
      if (!stack1.empty())
      {
        no_biconnected_components = no_biconnected_components + 1;
        cout << "biconnected_component_no: " << no_biconnected_components << '\n';
        while (!stack1.empty())
        {
         //cout << stack1.top().first << " " << stack1.top().second << '\n';
         
          set1.insert(stack1.top().first);
          set1.insert(stack1.top().second);
          stack1.pop();
        }
        for(auto itr : set1)
        {
          cout << itr << ' ';
        }
        cout << '\n';
        set1.clear();
      }
    }
  }
  cout << "No of biconnected_components: " << no_biconnected_components << '\n';
}
void setup(int n)
{
  adjacency_list.resize(n + 1);
  visited.resize(n + 1);
  low.resize(n + 1);
  parent.resize(n + 1);
  discovery_time.resize(n + 1);
  for (int i = 0; i < n + 1; i++)
  {
    visited[i] = false;
    parent[i] = -1;
    low[i] = INT_MAX - 1;
  }
}

void input_graph(int e)
{
  for (int i = 0; i < e; i++)
  {
    int a, b;
    cin >> a >> b;
    adjacency_list[a].push_back(b);
    adjacency_list[b].push_back(a);
  }
}
int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> no_of_vertex;
  cin >> no_of_edges;
  setup(no_of_vertex);
  input_graph(no_of_edges);
  biconnected_components();
  return 0;
}