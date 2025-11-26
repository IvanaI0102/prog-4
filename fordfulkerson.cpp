#include <bits/stdc++.h>
using namespace std;


int bfs(int n, int s, int t, vector<vector<int>> &graph, vector<vector<int>> &capacity, vector<int> &parent)
{
    parent.clear();
    for(int i=0;i<n;i++)
    {
        parent.push_back(-1);
    }

    parent[s] = -2;

    queue<pair<int,int>> q;
    q.push({s,INT_MAX});

    while(!q.empty())
    {
        auto h = q.front();
        q.pop();

        int node = h.first;
        int flow = h.second;

        for(auto next:graph[node])
        {
            if(parent[next]==-1 and capacity[node][next])
            {
                parent[next] = node;
                int newf = min(flow, capacity[node][next]);

                if(next == t)
                return newf;

                q.push({next,newf});
            }
        }


    }

    return 0;
}


int ford_fulkerson(int n, int s, int t, vector<vector<int>> & graph, vector<vector<int>> &capacity)
{
    int flow=0;
    int newf=0;
    vector<int> parent;
    vector<int> path;
    while(newf = bfs(n,s,t,graph,capacity,parent))
    {
        path.clear();
        path.push_back(t);
        int now = t;
        flow += newf;
        while(now!=s)
        {
           
            int before = parent[now];
            capacity[before][now] -= newf;
            capacity[now][before] += newf;
            now = before;
            path.push_back(now);
        }
        reverse(path.begin(), path.end());
        for(int i:path)
        cout << i << ' ';

        cout << endl;
    }

    return flow;
}


int main()
{
    int m = 0, n = 0, s=0, t=0;
    cin >> n >> m >> s >> t;

    vector<vector<int>> graph(n,vector<int>());
    vector<vector<int>> capacity(n,vector<int>(n,0));

    for(int i=0; i<m; i++)
    {
        int from=0,to=0,cap=0;
        cin >> from >> to >> cap;

        graph[from].push_back(to);
        graph[to].push_back(from);

        capacity[from][to] = cap;
    }

    cout << ford_fulkerson(n,s,t,graph,capacity);

    return 0;
}