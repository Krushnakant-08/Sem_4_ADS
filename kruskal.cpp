#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v ,w;
};

bool dfs(int src, int des, vector<vector<int>> &adj, vector<bool> &vis){
    if (src == des) return true;

    vis[src] = true;

    for(int neighbour : adj[src]){
        if(!vis[neighbour])
            if(dfs(neighbour, des, adj, vis))
                return true;
    }
    return false;
}

int main(){
    int v = 5;

    vector<Edge> edges = {
        {0, 1, 2},
        {0, 3, 6},
        {1, 2, 3},
        {1, 3, 8},
        {1, 4, 5},
        {2, 4, 7},
        {3, 4, 9}
    };

    sort(edges.begin(), edges.end(), [](Edge a, Edge b){ return a.w < b.w;});

    vector<vector<int>> adj(v);
    vector<Edge> mst;

    for(auto &e : edges){
        vector<bool> vis(v,false);
        if(!dfs(e.u, e.v, adj, vis)){
            adj[e.u].push_back(e.v);
            adj[e.v].push_back(e.u);
            mst.push_back(e);
        }
    }

    cout << "Edge \t Weight" << endl;
    for(auto e : mst){
        cout << e.u << " - " << e.v << " \t " << e.w << endl;
    }
}
