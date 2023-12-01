#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

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
  double distance;

  bool operator<(const Node& other) const {
    return distance > other.distance;
  }
};

vector<vector<int>> shortestPath(Graph graph, vector<int> sources) {
  // Initialize a priority queue with all vertices in sources.
  priority_queue<Node> queue;
  for (int source : sources) {
    queue.push({source, 0});
  }

  // Initialize a set of visited vertices.
  set<int> visited;

  // Initialize a vector to store shortest paths.
  vector<vector<int>> paths(graph.numVertices);

  // Dijkstra's algorithm
  while (!queue.empty()) {
    // Get the vertex with the smallest distance from the queue.
    Node current = queue.top();
    queue.pop();

    // If the vertex has already been visited, skip it.
    if (visited.count(current.vertex)) continue;

    // Mark the vertex as visited.
    visited.insert(current.vertex);

    // Add the vertex to the paths vector.
    paths[current.vertex].push_back(current.vertex);

    // Update the distances of its neighbors.
    for (Edge edge : graph.edges) {
      if (edge.src == current.vertex && !visited.count(edge.dest)) {
        double newDistance = current.distance + sqrt(pow(edge.weight, 2));
        if (newDistance < paths[edge.dest].size() || paths[edge.dest].empty()) {
          paths[edge.dest] = paths[current.vertex];
          paths[edge.dest].push_back(edge.dest);
          queue.push({edge.dest, newDistance});
        }
      }
    }
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

  // Create the set of source vertices.
  vector<int> sources = {0, 1};

  // Find the shortest paths between the source vertices and all other vertices.
  vector<vector<int>> paths = shortestPath(graph, sources);

  // Print the shortest path from source 0 to destination 2.
  for (int vertex : paths[0]) {
    cout << vertex << " ";
  }
  cout << endl;

  // Print the shortest path from source 1 to destination 3.
  for (int vertex : paths[1]) {
    cout << vertex << " ";
  }
  cout << endl;

  return 0;
}
