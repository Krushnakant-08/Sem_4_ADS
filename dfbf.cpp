#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

vector<vector<int>> GRAPH;
vector<bool> visited;

void DFS(int current)
{
    stack<int> st;
    st.push(current);

    while (!st.empty())
    {
        int start = st.top();
        st.pop();

        if (!visited[start])
        {
            visited[start] = true;
            cout << "Current on (DFS): " << start << endl;
        }

        for (int i = 0; i < GRAPH.size(); i++)
        {
            if (GRAPH[start][i] == 1 && !visited[i])
            {
                st.push(i);
            }
        }
    }
}

void BFS(int start)
{
    queue<int> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        cout << "Current on (BFS): " << current << endl;

        for (int i = 0; i < (int)GRAPH.size(); ++i)
        {
            if (GRAPH[current][i] == 1 && !visited[i])
            {
                q.push(i);
                visited[i] = true;
            }
        }
    }
}

int main()
{
    GRAPH = {
        {0, 0, 1, 1, 1},
        {0, 0, 1, 0, 1},
        {1, 1, 1, 0, 1},
        {1, 0, 1, 0, 1},
        {1, 1, 1, 1, 1}};

    int numNodes = (int)GRAPH.size();
    visited.assign(numNodes, false);

    int startNode = 0;
    cout << "Starting maze and finding min path using DFS from node " << startNode << endl;
    DFS(startNode);

    visited.assign(numNodes, false);
    cout << endl
         << endl;

    cout << "Starting maze and finding min path using BFS from node " << startNode << endl;
    BFS(startNode);

    return 0;
}