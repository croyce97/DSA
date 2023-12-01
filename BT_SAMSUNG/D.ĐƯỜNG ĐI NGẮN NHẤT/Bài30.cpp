#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
  int src;
  int dest;
  int weight;
};

struct Graph {
  int numVertices;
  vector<Edge> edges;
};

struct Node {
  int vertex;
  int distance;

  bool operator<(const Node& other) const {
    return distance < other.distance;
  }
};

vector<vector<int>> longestPath(Graph graph) {
  // Initialize a priority queue with all vertices.
  priority_queue<Node, vector<Node>, greater<Node>> queue;
  for (int vertex = 0; vertex < graph.numVertices; ++vertex) {
    queue.push({vertex, 0});
  }

  // Initialize a vector to store longest distances.
  vector<int> distances(graph.numVertices, 0);

  // Dijkstra's algorithm
  while (!queue.empty()) {
    // Get the vertex with the largest distance from the queue.
    Node current = queue.top();
    queue.pop();

    // If the vertex has already been processed, skip it.
    if (distances[current.vertex] > current.distance) continue;

    // Update the distances of its neighbors.
    for (Edge edge : graph.edges) {
      if (edge.src == current.vertex) {
        int newDistance = distances[current.vertex] + edge.weight;
        if (newDistance > distances[edge.dest]) {
          distances[edge.dest] = newDistance;
          queue.push({edge.dest, newDistance});
        }
      }
    }
  }

  // Initialize a vector to store longest paths.
  vector<vector<int>> paths(graph.numVertices);

  // Reconstruct the longest paths.
  for (int vertex = 0; vertex < graph.numVertices; ++vertex) {
    paths[vertex].push_back(vertex);

    for (Node parent = queue.top(); parent.vertex != vertex; parent = queue.top()) {
      queue.pop();
      paths[vertex].push_back(parent.vertex);
    }

    paths[vertex].reverse();
  }

  return paths;
}

int main() {
  // Create the graph.
  Graph graph = Graph{5};
  graph.edges.push_back({0, 1, 1});
  graph.edges.push_back({0, 2, 7});
  graph.edges.push_back({1, 2, 2});
  graph.edges.push_back({1, 3, 4});
  graph.edges.push_back({2, 3, 5});

  // Find the longest paths from all vertices.
  vector<vector<int>> paths = longestPath(graph);

  // Print the longest path from vertex 0.
  for (int vertex : paths[0]) {
    cout << vertex << " ";
  }
  cout << endl;

  return 0;
}
