#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18; 


int n, m;         
int src, snk;


vector<vector<int>> adj; 
vector<int> from, to;   
vector<long long> cap; 
vector<long long> flow;  


vector<int> lvl; 
vector<int> ptr; 


void add_edge(int a, int b, long long c) {
    
    from.push_back(a);
    to.push_back(b);
    cap.push_back(c);
    flow.push_back(0);
    adj[a].push_back((int)cap.size() - 1);

    
    from.push_back(b);
    to.push_back(a);
    cap.push_back(0);
    flow.push_back(0);
    adj[b].push_back((int)cap.size() - 1);
}


bool bfs() {
    fill(lvl.begin(), lvl.end(), -1); 
    queue<int> q;
    q.push(src);
    lvl[src] = 0;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int id : adj[v]) {
            int u = to[id];
            
            if (cap[id] - flow[id] < 1 || lvl[u] != -1)
                continue;
            lvl[u] = lvl[v] + 1;
            q.push(u);
        }
    }

    return lvl[snk] != -1; 
}


long long dfs(int v, long long pushed) {
    if (pushed == 0) return 0; 
    if (v == snk) return pushed;

    for (int &cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
        int id = adj[v][cid];
        int u = to[id];

      
        if (lvl[v] + 1 != lvl[u] || cap[id] - flow[id] < 1)
            continue;

        long long tr = dfs(u, min(pushed, cap[id] - flow[id]));
        if (tr == 0)
            continue;

        
        flow[id] += tr;
        flow[id ^ 1] -= tr;
        return tr;
    }
    return 0;
}


long long max_flow() {
    long long total_flow = 0;

    while (true) {
        if (!bfs()) 
            break;

        fill(ptr.begin(), ptr.end(), 0); 

        while (true) {
            long long pushed = dfs(src, INF);
            if (pushed == 0) break; 
            total_flow += pushed;
        }
    }

    return total_flow;
}

int main() {
   
    cin >> n >> m >> src >> snk;

    adj.assign(n, {});
    lvl.resize(n);
    ptr.resize(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        add_edge(a, b, c);
    }

    cout << "Maximum Flow: " << max_flow() << endl;
    return 0;
}
