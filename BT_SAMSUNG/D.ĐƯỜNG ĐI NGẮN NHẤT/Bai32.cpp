#include <iostream>
#include <vector>

using namespace std;

const int INF = INT_MAX;

struct Edge {
  int src;
  int dest;
  int weight;
};

struct Graph {
  int numVertices;
  vector<Edge> edges;
};

void shortestPath(Graph graph, vector<vector<int>>& distances) {
  // Initialize the distance matrix with infinity
  for (int i = 0; i < graph.numVertices; i++) {
    for (int j = 0; j < graph.numVertices; j++) {
      distances[i][j] = INF;
    }
  }

  // Initialize starting vertex
  int start = 0;
  distances[start][start] = 0;

  // Bellman-Ford algorithm
  for (int i = 0; i < graph.numVertices - 1; i++) {
    for (Edge edge : graph.edges) {
      int src = edge.src;
      int dest = edge.dest;
      int weight = edge.weight;

      if (distances[start][src] != INF && distances[start][src] + weight < distances[start][dest]) {
        distances[start][dest] = distances[start][src] + weight;
      }
    }
  }
}

int main() {
  // Create the weighted path graph
  Graph graph = Graph{4};
  graph.edges.push_back({0, 1, 1});
  graph.edges.push_back({1, 2, 2});
  graph.edges.push_back({2, 3, 3});

  // Initialize the distance matrix
  vector<vector<int>> distances(graph.numVertices, vector<int>(graph.numVertices, 0));

  // Preprocess the graph
  shortestPath(graph, distances);

  // Retrieve the shortest path distance between vertices 0 and 3
  int distance = distances[0][3];
  cout << "Shortest path distance from vertex 0 to vertex 3: " << distance << endl;

  return 0;
}
