#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

class Graph {
private:
    int V;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int vertices) : V(vertices), adj(vertices) {}

    void addEdge(int u, int v, int weight) {
        adj[u].emplace_back(v, weight);
    }

    void modifiedDijkstra(int source, int C) {
        vector<int> distance(C + 1, INF);
        vector<bool> visited(V, false);

        distance[0] = 0;

        for (int i = 0; i <= C; ++i) {
            int u = -1;

            // Chọn đỉnh có khoảng cách ngắn nhất chưa được thăm
            for (int j = 0; j < V; ++j) {
                if (!visited[j] && (u == -1 || distance[j] < distance[u])) {
                    u = j;
                }
            }

            if (distance[u] == INF) {
                break;  // Tất cả các đỉnh đã được thăm
            }

            visited[u] = true;

            // Relaxation
            for (const auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (weight <= C && distance[u] + weight < distance[weight]) {
                    distance[weight] = distance[u] + weight;
                }
            }
        }

        // In kết quả
        cout << "Shortest distances from source " << source << " with weight limit " << C << ":\n";
        for (int i = 0; i <= C; ++i) {
            cout << "To vertex " << i << ": " << (distance[i] == INF ? "INF" : to_string(distance[i])) << endl;
        }
    }
};

int main() {
    // Create a directed graph with weighted edges
    Graph graph(5);
    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 2, 5);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 4);
    graph.addEdge(2, 3, 1);
    graph.addEdge(3, 4, 3);

    // Find shortest distances with weight limit C
    graph.modifiedDijkstra(0, 6);

    return 0;
}
