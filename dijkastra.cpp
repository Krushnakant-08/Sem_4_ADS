#include <iostream>
#include <vector>
#include <limits>

using namespace std;

vector<int> dijkstra(const vector<vector<int>>& graph, int source) {
	int n = graph.size();
	const int INF = numeric_limits<int>::max();
	vector<int> dist(n, INF);
	vector<bool> visited(n, false);

	dist[source] = 0;

	for (int count = 0; count < n - 1; count++) {
		int u = -1;
		int minDist = INF;

		for (int i = 0; i < n; i++) {
			if (!visited[i] && dist[i] < minDist) {
				minDist = dist[i];
				u = i;
			}
		}

		if (u == -1) {
			break;
		}

		visited[u] = true;

		for (int v = 0; v < n; v++) {
			if (!visited[v] && graph[u][v] != 0 && dist[u] != INF &&
				dist[u] + graph[u][v] < dist[v]) {
				dist[v] = dist[u] + graph[u][v];
			}
		}
	}

	return dist;
}

int main() {
	int n;
	cout << "Enter number of vertices: ";
	cin >> n;

	vector<vector<int>> graph(n, vector<int>(n));
	cout << "Enter adjacency matrix (0 for no edge):\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> graph[i][j];
		}
	}

	int source;
	cout << "Enter source vertex (0 to " << n - 1 << "): ";
	cin >> source;

	vector<int> dist = dijkstra(graph, source);
	const int INF = numeric_limits<int>::max();

	cout << "\nShortest distances from source " << source << ":\n";
	for (int i = 0; i < n; i++) {
		cout << source << " -> " << i << " = ";
		if (dist[i] == INF) {
			cout << "INF";
		} else {
			cout << dist[i];
		}
		cout << "\n";
	}

	return 0;
}
