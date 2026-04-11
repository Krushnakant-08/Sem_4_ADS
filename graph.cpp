#include <iostream>
#include <queue>
#include <stack>
using namespace std;

void addEdge(int **a, int i, int j)
{
    a[i][j] = 1;
    a[j][i] = 1;
}

void dfs(int **a, int v, int start)
{
    stack<int> s;
    bool *visited = new bool[v];
    for (int i = 0; i < v; i++)
    {
        visited[i] = false;
    }
    
    cout << "DFS: ";
    visited[start] = true;
    cout << start << " ";
    for (int i = 0; i < v; i++)
    {
        if (a[start][i] == 1 && !visited[i])
        {
            s.push(i);
        }
    }

    while (!s.empty())
    {
        int curr = s.top();
        s.pop();
        if (!visited[curr])
        {
            visited[curr] = true;
            cout << curr << " ";
            for (int i = 0; i < v; i++)
            {
                if (a[curr][i] == 1 && !visited[i])
                {
                    s.push(i);
                }
            }
        }
    }
    cout<<endl;
}

void bfs(int **a, int v, int start)
{
    bool *visited = new bool[v];
    for (int i = 0; i < v; i++)
    {
        visited[i] = false;
    }

    queue<int> q;
    visited[start] = true;
    q.push(start);

    cout << "BFS: ";
    while (!q.empty())
    {
        int curr = q.front();
        cout << curr << " ";
        q.pop();
        for (int i = 0; i < v; i++)
        {
            if (a[curr][i] == 1 && !visited[i])
            {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    cout<<endl;

}


int main(){
    int **a;
    int m;
    cout << "Enter the number of vertices: ";
    cin >> m;
    a = new int*[m];
    for (int i = 0; i < m; i++)
    {
        a[i] = new int[m];
        for (int j = 0; j < m; j++)
        {
            a[i][j] = 0;
        }
    }

    addEdge(a, 0, 1);
    addEdge(a, 0, 2);   
    addEdge(a, 1, 3);
    addEdge(a, 1, 4);
    addEdge(a, 2, 5);
    addEdge(a, 2, 6);
    addEdge(a, 3, 2);
    addEdge(a, 4, 0);
    addEdge(a, 5, 0);

    // for(int i = 0; i < m; i++)
    // {
    //     for (int j = 0; j < m; j++)
    //     {
    //         cout << a[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    bfs(a, m, 0);
    dfs(a, m, 0);

}