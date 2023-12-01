#include <iostream>
#include <vector>

using namespace std;

struct Edge {
  int src;
  int dest;
};

struct Graph {
  int numVertices;
  vector<Edge> edges;
};

bool isHamiltonian(Graph graph) {
  vector<int> topologicalSort;
  topologicalSort(graph, topologicalSort);

  for (int i = 0; i < graph.numVertices - 1; i++) {
    if (graph.edges[topologicalSort[i]].dest != topologicalSort[i + 1]) {
      return false;
    }
  }

  return true;
}

void topologicalSort(Graph graph, vector<int>& topologicalSort) {
  topologicalSort.clear();

  // Khởi tạo một tập hợp chứa các đỉnh chưa được duyệt.
  vector<bool> visited(graph.numVertices, false);

  // Duyệt qua các đỉnh của đồ thị.
  for (int i = 0; i < graph.numVertices; i++) {
    if (!visited[i]) {
      topologicalSortDFS(graph, i, visited, topologicalSort);
    }
  }
}

void topologicalSortDFS(Graph graph, int vertex, vector<bool>& visited, vector<int>& topologicalSort) {
  // Đánh dấu đỉnh này là đã được duyệt.
  visited[vertex] = true;

  // Duyệt qua các đỉnh kề với đỉnh này.
  for (Edge edge : graph.edges) {
    if (edge.src == vertex && !visited[edge.dest]) {
      topologicalSortDFS(graph, edge.dest, visited, topologicalSort);
    }
  }

  // Thêm đỉnh này vào cuối thứ tự tô pô.
  topologicalSort.push_back(vertex);
}

int main() {
  Graph graph = Graph{5};
  graph.edges.push_back(Edge{0, 1});
  graph.edges.push_back(Edge{0, 2});
  graph.edges.push_back(Edge{1, 3});
  graph.edges.push_back(Edge{2, 3});
  graph.edges.push_back(Edge{3, 4});

  bool isHamiltonian = isHamiltonian(graph);
  if (isHamiltonian) {
    cout << "Đồ thị có đường đi Hamilton." << endl;
  } else {
    cout << "Đồ thị không có đường đi Hamilton." << endl;
  }

  return 0;
}
