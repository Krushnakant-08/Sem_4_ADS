#include <bits/stdc++.h>
using namespace std;

struct Department {
	string name;
	string location;
};

int findMinKey(int key[], bool mstSet[], int V) {
	int minVal = INT_MAX, index = -1;
	for (int v = 0; v < V; v++) {
		if (!mstSet[v] && key[v] < minVal) {
			minVal = key[v];
			index = v;
		}
	}
	return index;
}

void printMST(int parent[], int graph[][100], Department departments[], int V) {
	cout << "\nMinimum Spanning Tree Connections:\n";
	cout << "---------------------------------\n";

	int totalDistance = 0;
	for (int i = 1; i < V; i++) {
		if (parent[i] != -1) {
			cout << departments[parent[i]].name << " - " << departments[i].name
				 << " : " << graph[i][parent[i]] << " meters\n";
			totalDistance += graph[i][parent[i]];
		}
	}
	cout << "\nTotal cable length: " << totalDistance << " meters\n";
}

void findMST(int graph[][100], int V, Department departments[], int start) {
	int parent[100];
	int key[100];
	bool mstSet[100];

	for (int i = 0; i < V; i++) {
		key[i] = INT_MAX;
		mstSet[i] = false;
		parent[i] = -1;
	}

	key[start] = 0;

	for (int count = 0; count < V - 1; count++) {
		int u = findMinKey(key, mstSet, V);
		if (u == -1) {
			break;
		}
		mstSet[u] = true;

		for (int v = 0; v < V; v++) {
			if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
				parent[v] = u;
				key[v] = graph[u][v];
			}
		}
	}

	printMST(parent, graph, departments, V);
}

int main() {
	int V;
	cout << "Enter number of departments: ";
	cin >> V;
	cin.ignore();

	Department departments[100];
	int graph[100][100] = {0};

	cout << "\nEnter department details:\n";
	for (int i = 0; i < V; i++) {
		cout << "Department " << i << " name: ";
		getline(cin, departments[i].name);
		cout << "Location: ";
		getline(cin, departments[i].location);
	}

	cout << "\nEnter distances between departments:\n";
	for (int i = 0; i < V; i++) {
		for (int j = i + 1; j < V; j++) {
			cout << departments[i].name << " to " << departments[j].name << ": ";
			cin >> graph[i][j];
			graph[j][i] = graph[i][j];
		}
	}

	while (true) {
		cout << "\nAvailable departments:\n";
		for (int i = 0; i < V; i++) {
			cout << i << ": " << departments[i].name << endl;
		}

		int start;
		cout << "Enter starting department index (0-" << V - 1 << "): ";
		cin >> start;

		findMST(graph, V, departments, start);

		char again;
		cout << "Try another starting point? (y/n): ";
		cin >> again;
		if (again != 'y' && again != 'Y') {
			break;
		}
	}

	return 0;
}

