#include <bits/stdc++.h>
using namespace std;
int main()
{
    int brt=0, brr=0;
    cin >> brt >> brr;
    vector<vector<int>> graph(brt);
    
    int n=0, m=0;
    for(int i=0; i<brr; i++){
        cin >> n>> m;
        graph[n].push_back(m);
        graph[m].push_back(n);
    }
    
    for(int i=0; i<graph.size(); i++){
        for(int j=0; j<graph[i].size(); j++){
            cout << graph[i][j] << " ";
        }
        if(graph[i].size()==0) cout << "*empty*";
        cout << endl;
    }
    return 0;
}