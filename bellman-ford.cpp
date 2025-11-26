#include <bits/stdc++.h>
using namespace std;


vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
    vector<int> dist(V, 1e8); 
    dist[src] = 0;

 
    for (int i = 0; i < V; i++) {
        for (auto &edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];

            if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                if (i == V - 1) {
                   
                    return {-1};
                }
                dist[v] = dist[u] + wt;
            }
        }
    }

    return dist;
}


vector<vector<int>> generateConnectedGraph(int n) {
    vector<vector<int>> edges;
    srand(time(0));

    
    for (int i = 1; i < n; i++) {
        int w = rand() % 21 - 3; 
        edges.push_back({i - 1, i, w});
    }

  
    for (int i = 0; i < n; i++) {
        int u = rand() % n;
        int v = rand() % n;
        if (u != v) {
            bool exists = false;
            for (auto &e : edges) {
                if ((e[0] == u && e[1] == v) || (e[0] == v && e[1] == u)) {
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                int w = rand() % 21 - 4;
                edges.push_back({u, v, w});
            }
        }
    }

    return edges;
}
int main() {
    int n = 50;                
    ofstream fout("output.txt");
    if (!fout.is_open()) {
        cerr << "Error\n";
        return 1;
    }

    for (int g = 1; g <= 10; g++) {
        auto edges = generateConnectedGraph(n);

        
        cout << "Graph " << g << "\n";
        cout << "Generirani rebra (u v w):\n";
        for (auto &e : edges) {
            cout << e[0] << " " << e[1] << " " << e[2] << "\n";
        }

        
        vector<int> dist = bellmanFord(n, edges, 0);

    
        fout << "Graph " << g << " \n";
        fout << "Generirani rabovi (u v w):\n";
        for (auto &e : edges) {
            fout << e[0] << " " << e[1] << " " << e[2] << "\n";
        }
        fout << "\n";

        if (dist.size() == 1 && dist[0] == -1) {
            fout << "Negativen ciklus!\n";
        } else {
            for (int i = 0; i < n; i++) {
                fout << "Rastojanie od 0 do " << i << " = ";
                if (dist[i] == 1e8) fout << "INF";
                else fout << dist[i];
                fout << "\n";
            }
        }
        fout << "\n";
    }

    fout.close();
    return 0;
}