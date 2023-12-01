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

