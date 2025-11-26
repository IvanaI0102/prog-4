#include <bits/stdc++.h>
using namespace std;

const int inf = 1000000000;

int n;
vector<vector<int>> capacity, flow;
vector<int> height, excess, seen;
queue<int> excess_vertices;

void push(int u, int v) {
    int d = min(excess[u], capacity[u][v] - flow[u][v]);
    flow[u][v] += d;
    flow[v][u] -= d;
    excess[u] -= d;
    excess[v] += d;
    if (d && excess[v] == d)
        excess_vertices.push(v);
}

void relabel(int u) {
    int d = inf;
    for (int i = 0; i < n; i++) {
        if (capacity[u][i] - flow[u][i] > 0)
            d = min(d, height[i]);
    }
    if (d < inf)
        height[u] = d + 1;
}

void discharge(int u) {
    while (excess[u] > 0) {
        if (seen[u] < n) {
            int v = seen[u];
            if (capacity[u][v] - flow[u][v] > 0 && height[u] > height[v])
                push(u, v);
            else
                seen[u]++;
        } else {
            relabel(u);
            seen[u] = 0;
        }
    }
}

int max_flow(int s, int t) {
    height = vector<int>(n, 0);
    height[s] = n;

    flow = vector<vector<int>>(n, vector<int>(n, 0));
    excess = vector<int>(n, 0);

    excess[s] = inf;
    for (int i = 0; i < n; i++) {
        if (i != s)
            push(s, i);
    }

    seen = vector<int>(n, 0);

    while (!excess_vertices.empty()) {
        int u = excess_vertices.front();
        excess_vertices.pop();
        if (u != s && u != t)
            discharge(u);
    }

    int maxflow = 0;
    for (int i = 0; i < n; i++)
        maxflow += flow[i][t];
    return maxflow;
}

void generateRandomGraph(int maxCapacity = 20) {
    srand(time(0));
    capacity.assign(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j)
                capacity[i][j] = rand() % (maxCapacity + 1);
        }
    }
}

void printGraph() {
    cout << "Capacity Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << capacity[i][j] << " ";
        cout << "\n";
    }
}

int main() {
    cout << "Enter number of nodes: ";
    cin >> n;

    capacity.assign(n, vector<int>(n, 0));

    cout << "Choose input method:\n1 = Random graph\n2 = Manual edge list input\n";
    int choice;
    cin >> choice;

    if (choice == 1) {
        int max_cap;
        cout << "Enter maximum capacity for edges: ";
        cin >> max_cap;

        srand(time(0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j)
                    capacity[i][j] = rand() % (max_cap + 1);
            }
        }
    } 
    else if (choice == 2) {
        int m;
        cout << "Enter number of edges: ";
        cin >> m;
        cout << endl<<"Enter each edge as: from to capacity"<<endl;
        for (int i = 0; i < m; i++) {
            int u, v, cap;
            cin >> u >> v >> cap;
            capacity[u][v] = cap;
        }
    }

    int s, t;
    cout << "Enter source and sink: "<<endl;
    cin >> s >> t;

    int result = max_flow(s, t);
    cout << "Maximum flow = " << result << endl;

    return 0;
}