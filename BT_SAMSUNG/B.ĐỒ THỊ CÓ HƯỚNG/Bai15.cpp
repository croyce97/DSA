#include <iostream>
#include <queue>

using namespace std;

struct Edge {
  int src;
  int dest;
};

struct Graph {
  int numVertices;
  vector<Edge> edges;
};

void topologicalSort(Graph graph, vector<bool>& visited, vector<int>& topologicalSort) {
  // Khởi tạo mảng bậc vào.
  vector<int> indegree(graph.numVertices, 0);

  // Duyệt qua tất cả các cạnh.
  for (Edge edge : graph.edges) {
    indegree[edge.dest]++;
  }

  // Thêm các đỉnh nguồn vào hàng đợi.
  queue<int> queue;
  for (int i = 0; i < graph.numVertices; i++) {
    if (indegree[i] == 0) {
      queue.push(i);
    }
  }

  // Sắp xếp tô pô.
  while (!queue.empty()) {
    // Lấy một đỉnh nguồn ra khỏi hàng đợi.
    int vertex = queue.front();
    queue.pop();

    // Đánh nhãn cho đỉnh này.
    visited[vertex] = true;
    topologicalSort.push_back(vertex);

    // Giảm bậc vào của các đỉnh kề.
    for (Edge edge : graph.edges) {
      if (edge.src == vertex) {
        indegree[edge.dest]--;

        // Nếu bậc vào của một đỉnh giảm về 0 thì thêm đỉnh đó vào hàng đợi.
        if (indegree[edge.dest] == 0) {
          queue.push(edge.dest);
        }
      }
    }
  }
}

int main() {
  Graph graph = Graph{5};
  graph.edges.push_back(Edge{0, 1});
  graph.edges.push_back(Edge{0, 2});
  graph.edges.push_back(Edge{1, 3});
  graph.edges.push_back(Edge{2, 3});
  graph.edges.push_back(Edge{3, 4});

  vector<bool> visited(graph.numVertices, false);
  vector<int> topologicalSort;
  topologicalSort.reserve(graph.numVertices);

  topologicalSort(graph, visited, topologicalSort);

  for (int vertex : topologicalSort) {
    cout << vertex << " ";
  }
  cout << endl;

  return 0;
}
