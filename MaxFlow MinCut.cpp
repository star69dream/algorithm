#include <bits/stdc++.h>
#define V 100
using namespace std;
 
int bfs(int rGraph[V][V], int s, int t, int parent[])  // Returns true if there is a path from s to t in graph. and store the path 
{
    bool visited[V];
    memset(visited, 0, sizeof(visited));
    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v = 0; v < V; v++)
        {
            if (visited[v] == false && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return (visited[t] == true);
}
 
void dfs(int rGraph[V][V], int s, bool visited[]) // A DFS based function to find all reachable vertices from s. if reachable from s to i, then visited[i] become true, in here we also use bfs
{
    visited[s] = true;
    for (int i = 0; i < V; i++)
    {
        if (rGraph[s][i] && !visited[i])
           dfs(rGraph, i, visited);
    }
}
 
void maxFlowMinCut(int graph[V][V], int s, int t) // MaxFolw MinCut function
{
    int u, v;
    int rGraph[V][V];
    for (u = 0; u < V; u++)
    {
        for (v = 0; v < V; v++)
             rGraph[u][v] = graph[u][v];   ///  rGraph[i][j] indicates capacity of edge i-j
    }
    int parent[V];
    while (bfs(rGraph, s, t, parent))  // Augment the flow while there is a path from source to target
    {
        int path_flow = 65536;    /// init max flow.
        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
        for (v = t; v != s; v = parent[v])    /// update capacities of the edges
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
    }
    ///  Flow is maximum now,
    bool visited[V];
    memset(visited, 0, sizeof(visited));
    dfs(rGraph, s, visited); ///  find vertices reachable from s
    int sum = 0;
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (visited[i] && !visited[j] && graph[i][j]){
            	sum += graph[i][j];
			}
        }
    }
    printf("Max flow: %d\n", sum);
    printf("Min cut edges:\n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (visited[i] && !visited[j] && graph[i][j]){
            	cout << i << " - " << j << endl;
			}
        }
    }

    return;
}
 
int main()
{
	freopen("input.txt", "r", stdin);
	int nVertex, nEdge;
	int stV, etV, cpE;
	
	scanf("%d", &nVertex);
	scanf("%d", &nEdge);
	int graph[100][100];
	for (int i = 0 ; i < V ; i ++) {
		for (int j = 0 ; j < V ; j ++) {
			graph[i][j] = 0;
		}
	}
	for(int i = 0 ; i < nEdge ; i ++) {
		scanf("%d %d %d", &stV, &etV, &cpE);
		graph[stV][etV] = cpE;
	}
    maxFlowMinCut(graph, 0, nVertex - 1);   /// get result
    return 0;
}
