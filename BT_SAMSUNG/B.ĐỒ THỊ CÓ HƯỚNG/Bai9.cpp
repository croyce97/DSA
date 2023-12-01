#include <iostream>
#include <list>

using namespace std;

struct Edge {
  int src;
  int dest;
};

struct Graph {
  int numVertices;
  list<Edge> edges;
};

bool isEulerian(Graph graph) {
  int oddVertices = 0;
  for (int i = 0; i < graph.numVertices; i++) {
    int inDegree = 0, outDegree = 0;
    for (Edge edge : graph.edges) {
      if (edge.src == i) {
        outDegree++;
      } else if (edge.dest == i) {
        inDegree++;
      }
    }
    if (inDegree != outDegree) {
      oddVertices++;
    }
  }
  return oddVertices <= 2;
}

list<int> findEulerianCycle(Graph graph) {
  if (!isEulerian(graph)) {
    return {};
  }

  list<int> path;
  int currentVertex = 0;

  while (true) {
    list<Edge> adjList = getAdjacentEdges(graph, currentVertex);
    if (adjList.empty()) {
      if (path.empty() || currentVertex != path.front()) {
        return {};
      }
      currentVertex = path.back();
      path.pop_back();
    } else {
      Edge edgeToRemove = adjList.front();
      adjList.pop_front();
      graph.edges.remove(edgeToRemove);
      currentVertex = edgeToRemove.dest;
      path.push_back(edgeToRemove.dest);
    }
  }

  return path;
}

list<Edge> getAdjacentEdges(Graph graph, int vertex) {
  list<Edge> adjList;
  for (Edge edge : graph.edges) {
    if (edge.src == vertex || edge.dest == vertex) {
      adjList.push_back(edge);
    }
  }
  return adjList;
}

int main() {
  Graph graph = Graph{4};
  graph.edges.push_back(Edge{0, 1});
  graph.edges.push_back(Edge{1, 2});
  graph.edges.push_back(Edge{2, 3});
  graph.edges.push_back(Edge{3, 0});

  list<int> cycle = findEulerianCycle(graph);
  if (!cycle.empty()) {
    cout << "Eulerian cycle: ";
    for (int vertex : cycle) {
      cout << vertex << " ";
    }
    cout << endl;
  } else {
    cout << "No Eulerian cycle" << endl;
  }

  return 0;
}
