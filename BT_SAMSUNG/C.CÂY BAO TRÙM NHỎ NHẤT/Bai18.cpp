#include <iostream>
#include <vector>
#include <algorithm>

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

vector<Edge> findMinSpanningTree(Graph graph) {
  // Sắp xếp các cạnh theo trọng số giảm dần.
  sort(graph.edges.begin(), graph.edges.end(), [](Edge a, Edge b) { return a.weight > b.weight; });

  // Khởi tạo một cây bao trùm rỗng.
  vector<Edge> tree;

  // Lặp lại qua tất cả các cạnh.
  for (Edge edge : graph.edges) {
    // Nếu xóa cạnh này không làm đồ thị mất liên thông thì thêm nó vào cây bao trùm.
    if (isConnected(graph, edge.src, edge.dest)) {
      tree.push_back(edge);
    }
  }

  return tree;
}

bool isConnected(Graph graph, int src, int dest) {
  // Khởi tạo một tập hợp chứa các đỉnh đã được duyệt.
  vector<bool> visited(graph.numVertices, false);

  // Khởi tạo một hàng đợi chứa đỉnh gốc.
  queue<int> queue;
  queue.push(src);

  // Tìm kiếm theo chiều sâu.
  while (!queue.empty()) {
    // Lấy một đỉnh ra khỏi hàng đợi.
    int vertex = queue.front();
    queue.pop();

    // Đánh dấu đỉnh này là đã được duyệt.
    visited[vertex] = true;

    // Duyệt qua các đỉnh kề.
    for (Edge edge : graph.edges) {
      if (edge.src == vertex && !visited[edge.dest]) {
        queue.push(edge.dest);
      }
    }
  }

  // Nếu đỉnh đích đã được duyệt thì đồ thị vẫn liên thông.
  return visited[dest];
}

int main() {
  Graph graph = Graph{5};
  graph.edges.push_back(Edge{0, 1, 1});
  graph.edges.push_back(Edge{0, 2, 7});
  graph.edges.push_back(Edge{1, 3, 2});
  graph.edges.push_back(Edge{2, 3, 4});
  graph.edges.push_back(Edge{3, 4, 5});

  vector<Edge> tree = findMinSpanningTree(graph);

  for (Edge edge : tree) {
    cout << "(" << edge.src << ", " << edge.dest << ", " << edge.weight << ")" << endl;
  }

  return 0;
}
