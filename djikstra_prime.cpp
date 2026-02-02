#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void generatePrimesDijkstra(int limit) {
    if (limit < 2) return;
    priority_queue<pair<int, int>, 
                   vector<pair<int, int>>, 
                   greater<pair<int, int>>> pq;

   
    cout << 2 << " ";
    pq.push({4, 2});

    for (int n = 3; n <= limit; n++) {
       
        if (n < pq.top().first) {
            cout << n << " ";
           
            pq.push({n * n, n});
        } else {
            
            while (n == pq.top().first) {
                pair<int, int> current = pq.top();
                pq.pop();
                
                current.first += current.second;
                pq.push(current);
            }
        }
    }
    cout << endl;
}

int main() {
    int n;
    if (!(cin >> n)) return 0; //vnesi limit

    cout << n << endl;
    generatePrimesDijkstra(n);

    return 0;
}