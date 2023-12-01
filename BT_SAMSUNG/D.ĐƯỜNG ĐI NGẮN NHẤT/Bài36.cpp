#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int source, destination, weight;
};

class Graph {
private:
    int V;
    vector<Edge> edges;

public:
    Graph(int vertices) : V(vertices) {}

    void addEdge(int u, int v, int weight) {
        edges.push_back({u, v, weight});
    }

    pair<int, int> findEdgeWithMaxIncrease(int source, int target) {
        vector<int> distance(V, INF);
        distance[source] = 0;

        // Relaxation steps
        for (int i = 0; i < V - 1; ++i) {
            for (const Edge& edge : edges) {
                if (distance[edge.source] != INF && distance[edge.source] + edge.weight < distance[edge.destination]) {
                    distance[edge.destination] = distance[edge.source] + edge.weight;
                }
            }
        }

        // Check for negative cycles
        for (const Edge& edge : edges) {
            if (distance[edge.source] != INF && distance[edge.source] + edge.weight < distance[edge.destination]) {
                cout << "Graph contains negative cycle, unable to find a path." << endl;
                return {-1, -1}; // There is a negative cycle
            }
        }

        // Find edge with max increase in shortest path
        int maxIncrease = 0;
        pair<int, int> result = {-1, -1};

        for (const Edge& edge : edges) {
            int newDistance = distance[edge.source] + edge.weight;
            if (newDistance < distance[edge.destination] && newDistance - distance[edge.destination] < maxIncrease) {
                maxIncrease = newDistance - distance[edge.destination];
                result = {edge.source, edge.destination};
            }
        }

        return result;
    }
};

int main() {
    // Create a directed graph with weighted edges
    Graph graph(5);
    graph.addEdge(0, 1, 2);
    graph.addEdge(1, 2, 3);
    graph.addEdge(2, 3, 1);
    graph.addEdge(3, 4, 4);
    graph.addEdge(0, 4, 5);

    // Find the edge with the maximum increase in shortest path
    pair<int, int> result = graph.findEdgeWithMaxIncrease(0, 4);

    if (result.first == -1 && result.second == -1) {
        cout << "No edge found (negative cycle present)." << endl;
    } else {
        cout << "Edge with maximum increase in shortest path: " << result.first << " --> " << result.second << endl;
    }

    return 0;
}
