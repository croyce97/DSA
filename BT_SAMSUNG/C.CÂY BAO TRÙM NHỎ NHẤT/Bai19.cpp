#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int vertices) : V(vertices), adj(vertices) {}

    void addEdge(int u, int v, int weight) {
        adj[u].emplace_back(v, weight);
        adj[v].emplace_back(u, weight);
    }

    void DFS(int u, int parent, vector<int>& disc, vector<int>& low, vector<bool>& visited, vector<pair<int, int>>& criticalEdges) {
        static int time = 0;
        disc[u] = low[u] = ++time;
        visited[u] = true;

        for (const auto& neighbor : adj[u]) {
            int v = neighbor.first;

            if (!visited[v]) {
                DFS(v, u, disc, low, visited, criticalEdges);
                low[u] = min(low[u], low[v]);

                if (low[v] > disc[u]) {
                    // Cạnh (u, v) là cạnh cầu
                    criticalEdges.push_back({u, v});
                }
            } else if (v != parent) {
                low[u] = min(low[u], disc[v]);
            }
        }
    }

    void findCriticalEdges() {
        vector<int> disc(V, -1);
        vector<int> low(V, -1);
        vector<bool> visited(V, false);
        vector<pair<int, int>> criticalEdges;

        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                DFS(i, -1, disc, low, visited, criticalEdges);
            }
        }

        // In danh sách các cạnh cầu
        cout << "Critical Edges:" << endl;
        for (const auto& edge : criticalEdges) {
            cout << edge.first << " --> " << edge.second << endl;
        }
    }
};

int main() {
    // Tạo đồ thị cây bao trùm nhỏ nhất
    Graph graph(6);
    graph.addEdge(0, 1, 2);
    graph.addEdge(1, 2, 1);
    graph.addEdge(2, 0, 3);
    graph.addEdge(1, 3, 4);
    graph.addEdge(3, 4, 5);
    graph.addEdge(4, 5, 6);

    // Tìm các cạnh cầu (critical edges)
    graph.findCriticalEdges();

    return 0;
}
