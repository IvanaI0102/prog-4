#include <iostream>
#include <bits/stdc++.h>
using namespace std;
void dijkstra(int pocetok, int num, vector<vector<pair<int, int>>> &graph, vector<int>&rast)
{
    bool pominato[num]; //niza so mi kazue dali nodeot e poseten
    for(int i=0; i<num; i++)
    {
        rast[i]=INT_MAX; //site rast gi prave beskonecno
        pominato[i]=0; //uste nikoj node ne e pominat
    }
    priority_queue<pair<int, int>>pq; //za da go odbere nodeot so najratko rast
    pq.push({0, pocetok}); //pocnuvas so rast 0 od pocetniot node
    rast[pocetok]=0; // rast od pocetniot node do sebe e sekogas 0
    while(!pq.empty()) //se dodeka site nodeovi se pominati
    {
        auto sega = pq.top();
        pq.pop();
        
        int node = sega.second;
        int n = -sega.first; //momentalno najkratko rastojanie do ovoj node
        
        for(auto i:graph[n])
        {
            int nareden = i.second;
            int donareden = i.first;
            
            if(pominato[nareden]==0)
            {
                pominato[nareden]=1;
                if(rast[nareden]>n+donareden)
                {
                    rast[nareden] = n+donareden;
                    pq.push({-rast[nareden], nareden});
                }
                }
            
        }
        
        }
    }


int main(){
    int n=0,m=0;
    char kakov='\0';
    cin >> n >> m;
    cout << "Directed or not? d/u" << endl;
    cin >> kakov;

    vector<vector<pair<int,int>>> adj_list(n, vector<pair<int,int>>());

    for(int i=0;i<m;i++)
    {
        int from=0, to=0, weight=0;
        cin >> from >> to >> weight;

        if(kakov=='d')
        {
            adj_list[from].push_back({weight,to});
        }
        else if (kakov=='u')
        {
            adj_list[from].push_back({weight,to});
            adj_list[to].push_back({weight,from});
        }
    }

    vector<int> dist(n,0);

    dijkstra(0,n,adj_list,dist);

    for(int i=0; i<n; i++)
    cout << dist[i] << ' ';

 
   

}