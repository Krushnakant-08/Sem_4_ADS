#include<iostream>
#include<climits>
#include<string>
using namespace std;

#define MAX 8

// Train stations (same as tree.cpp)
string stations[MAX] = {
    "CSMT",      // 0
    "Dadar",     // 1
    "Kalyan",    // 2
    "Karjat",    // 3
    "Lonavala",  // 4
    "Daund",     // 5
    "Nashik",    // 6
    "Sinnar"     // 7
};

class Graph {
private:
    int AM[MAX][MAX];   // Adjacency matrix (distances in km)
    int nV;

public:
    Graph(int V) {
        nV = V;
        // Initialize: 0 for self, INT_MAX for no direct route
        for(int i = 0; i < MAX; i++)
            for(int j = 0; j < MAX; j++)
                AM[i][j] = (i == j) ? 0 : INT_MAX;
    }

    void addEdge(int u, int v, int w) {
        AM[u][v] = w;
        AM[v][u] = w;
    }

    // Build the train network
    void buildNetwork() {
        // CSMT(0) -- Dadar(1): 8 km
        addEdge(0, 1, 8);
        // Dadar(1) -- Kalyan(2): 54 km
        addEdge(1, 2, 54);
        // Kalyan(2) -- Karjat(3): 45 km
        addEdge(2, 3, 45);
        // Karjat(3) -- Lonavala(4): 60 km
        addEdge(3, 4, 60);
        // Lonavala(4) -- Daund(5): 75 km
        addEdge(4, 5, 75);
        // Dadar(1) -- Nashik(6): 160 km
        addEdge(1, 6, 160);
        // Nashik(6) -- Sinnar(7): 30 km
        addEdge(6, 7, 30);
        // Kalyan(2) -- Nashik(6): 120 km
        addEdge(2, 6, 120);
        // Daund(5) -- Sinnar(7): 90 km
        addEdge(5, 7, 90);
        // CSMT(0) -- Kalyan(2): 60 km (direct express)
        addEdge(0, 2, 60);
    }

    // Display the network
    void displayNetwork() {
        cout << "\n=== Train Network (Direct Routes) ===" << endl;
        cout << "------------------------------------------------------" << endl;
        cout << "From\t\t\tTo\t\t\tDist(km)" << endl;
        cout << "------------------------------------------------------" << endl;
        for(int i = 0; i < nV; i++) {
            for(int j = i+1; j < nV; j++) {
                if(AM[i][j] != INT_MAX) {
                    cout << stations[i] << "\t\t\t"
                         << stations[j] << "\t\t\t"
                         << AM[i][j] << " km" << endl;
                }
            }
        }
        cout << "------------------------------------------------------" << endl;
    }

    // Dijkstra's algorithm with path tracking
    void dijkstra(int src, int dest) {
        int distance[MAX];
        int parent[MAX];
        bool visited[MAX];

        for(int i = 0; i < nV; i++) {
            distance[i] = INT_MAX;
            parent[i] = -1;
            visited[i] = false;
        }
        distance[src] = 0;

        for(int i = 0; i < nV; i++) {
            // Find unvisited vertex with minimum distance
            int u = -1;
            int minDist = INT_MAX;
            for(int j = 0; j < nV; j++) {
                if(!visited[j] && distance[j] < minDist) {
                    minDist = distance[j];
                    u = j;
                }
            }

            if(u == -1) break; // All remaining vertices unreachable
            visited[u] = true;

            // Relax neighbors
            for(int v = 0; v < nV; v++) {
                if(AM[u][v] != INT_MAX && !visited[v]) {
                    if(distance[u] + AM[u][v] < distance[v]) {
                        distance[v] = distance[u] + AM[u][v];
                        parent[v] = u;
                    }
                }
            }
        }

        // Print all shortest distances from source
        cout << "\n=== Shortest Distances from " << stations[src] << " ===" << endl;
        cout << "------------------------------------------------------" << endl;
        cout << "Destination\t\tDistance(km)\tPath" << endl;
        cout << "------------------------------------------------------" << endl;

        for(int i = 0; i < nV; i++) {
            if(i == src) continue;
            cout << stations[i] << "\t\t\t";
            if(distance[i] == INT_MAX) {
                cout << "Unreachable\t-" << endl;
            } else {
                cout << distance[i] << " km\t\t";
                // Reconstruct path
                int path[MAX], pLen = 0, cur = i;
                while(cur != -1) {
                    path[pLen++] = cur;
                    cur = parent[cur];
                }
                for(int p = pLen - 1; p >= 0; p--) {
                    cout << stations[path[p]];
                    if(p > 0) cout << " -> ";
                }
                cout << endl;
            }
        }
        cout << "------------------------------------------------------" << endl;

        // Specific source-to-destination result
        if(dest != -1 && dest != src) {
            cout << "\n=== Result ===" << endl;
            if(distance[dest] == INT_MAX) {
                cout << "No route found between "
                     << stations[src] << " and " << stations[dest] << endl;
            } else {
                cout << "Shortest distance from " << stations[src]
                     << " to " << stations[dest]
                     << " = " << distance[dest] << " km" << endl;

                // Print path
                cout << "Route: ";
                int path[MAX], pLen = 0, cur = dest;
                while(cur != -1) {
                    path[pLen++] = cur;
                    cur = parent[cur];
                }
                for(int p = pLen - 1; p >= 0; p--) {
                    cout << stations[path[p]];
                    if(p > 0) cout << " -> ";
                }
                cout << endl;
            }
        }
    }
};

int main() {
    Graph g(MAX);
    g.buildNetwork();
    g.displayNetwork();

    int src, dest;
    cout << "\n=== Train Station Index ===" << endl;
    for(int i = 0; i < MAX; i++)
        cout << i << " : " << stations[i] << endl;

    cout << "\nEnter source station index: ";
    cin >> src;
    cout << "Enter destination station index: ";
    cin >> dest;

    if(src < 0 || src >= MAX || dest < 0 || dest >= MAX) {
        cout << "Invalid station index!" << endl;
        return 1;
    }

    g.dijkstra(src, dest);

    return 0;
}