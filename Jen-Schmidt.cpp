#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graph;
vector<bool> dfs_visited;
vector<int> schmidt_visited;
vector<int> dfs_discovery_time_vs_node;
vector<int> dfs_discovery_node_vs_time;
vector<vector<int>> dfs_tree;
vector<vector<int>> back_edges;

void setup(int n)
{
    graph.resize(n + 1);
    dfs_tree.resize(n + 1);
    back_edges.resize(n + 1);
    dfs_visited.resize(n + 1);
    schmidt_visited.resize(n + 1);
    dfs_discovery_node_vs_time.resize(n + 1);
    for (int i = 0; i < n + 1; i++)
    {
        dfs_visited[i] = false;
        schmidt_visited[i] = false;
    }
}

void input_graph(int e)
{
    for (int i = 0; i < e; i++)
    {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
}

void print_graph()
{
    cout << "graph is \n";
    for (int i = 1; i <= graph.size(); i++)
    {
        cout << i << ": ";
        for (int j = 0; j < graph[i].size(); j++)
        {
            cout << graph[i][j] << ",";
        }
        cout << "\n";
    }
    cout << "\n";
}

void print_dfs_tree()
{
    cout << "dfs tree:\n";
    for (int i = 1; i <= dfs_tree.size(); i++)
    {
        cout << i << ": ";
        for (int j = 0; j < dfs_tree[i].size(); j++)
        {
            cout << dfs_tree[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void print_back_edges()
{
    cout << "back edges:\n";
    for (int i = 1; i <= back_edges.size(); i++)
    {
        cout << i << ": ";
        for (int j = 0; j < back_edges[i].size(); j++)
        {
            cout << back_edges[i][j] << " ";
        }
        cout << "\n";
    }
}

void dfs(int start, int parent)
{
    dfs_visited[start] = true;
    dfs_discovery_time_vs_node.push_back(start);
    dfs_discovery_node_vs_time[start] = dfs_discovery_time_vs_node.size() - 1;
    for (int neighbour : graph[start])
    {
        if (dfs_visited[neighbour] == false)
        {
            dfs_tree[neighbour].push_back(start);
            dfs(neighbour, start);
        }
        else
        {
            if (neighbour == parent)
            {
                continue;
            }
            if (dfs_discovery_node_vs_time[neighbour] < dfs_discovery_node_vs_time[start])
            {
                back_edges[neighbour].push_back(start);
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, e; // n = num of nodes, e = num of edges
    cin >> n >> e;
    setup(n);
    input_graph(e);

#ifdef PRINT_GRAPH
    print_graph();
#endif

    dfs(1, -1);

#ifdef PRINT_DFS_TREE
    print_dfs_tree();
#endif
#ifdef PRINT_BACK_EDGES
    print_back_edges();
#endif
    int num_cycles = 0;
    for (auto ear_start_vertex : dfs_discovery_time_vs_node)
    {
        schmidt_visited[ear_start_vertex] = true;
        for (auto backnode : back_edges[ear_start_vertex])
        {
            cout << "ear: " << ear_start_vertex << ",";
            cout << backnode << ",";
            auto next_node = backnode;
            while (schmidt_visited[next_node] == false)
            {
                schmidt_visited[next_node] = true;
                next_node = dfs_tree[next_node][0];
                cout << next_node << ",";
                if (next_node == ear_start_vertex)
                    num_cycles++;
            }
            cout << "\n";
        }
    }
    if (num_cycles == 1)
        cout << "The only cycle was C1, so the graph is one entire biCC\n";
    else if (num_cycles > 1)
        cout << "There was another cycle other than C1, so the graph is has multiple biCC\n";
}