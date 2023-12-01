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

vector<vector<Edge>> prim(Graph graph) {
  // Khởi tạo một rừng bao trùm rỗng.
  vector<vector<Edge>> forest;
  forest.resize(graph.numVertices);

  // Khởi tạo một tập hợp chứa các đỉnh chưa được duyệt.
  vector<bool> visited(graph.numVertices, false);

  // Chọn một đỉnh bất kỳ làm đỉnh gốc.
  int source = 0;

  // Thêm đỉnh gốc vào rừng bao trùm.
  visited[source] = true;
  forest[source].push_back(Edge{source, source, 0});

  // Lặp lại cho đến khi tất cả các đỉnh được duyệt.
  while (!visited.empty()) {
    // Tìm cạnh có trọng số nhỏ nhất nối một đỉnh đã được duyệt với một đỉnh chưa được duyệt.
    int minWeight = INT_MAX;
    int minVertex = -1;
    for (int i = 0; i < graph.numVertices; i++) {
      if (visited[i]) {
        for (Edge edge : forest[i]) {
          if (!visited[edge.dest] && edge.weight < minWeight) {
            minWeight = edge.weight;
            minVertex = edge.dest;
          }
        }
      }
    }

    // Nếu không tìm thấy cạnh nào thì kết thúc thuật toán.
    if (minVertex == -1) {
      break;
    }

    // Thêm cạnh có trọng số nhỏ nhất vào rừng bao trùm.
    forest[source].push_back(Edge{source, minVertex, minWeight});
    forest[minVertex].push_back(Edge{minVertex, source, minWeight});

    // Đánh dấu đỉnh mới được thêm vào là đã được duyệt.
    visited[minVertex] = true;
  }

  return forest;
}

int main() {
  Graph graph = Graph{5};
  graph.edges.push_back(Edge{0, 1, 1});
  graph.edges.push_back(Edge{0, 2, 7});
  graph.edges.push_back(Edge{1, 3, 2});
  graph.edges.push_back(Edge{2, 3, 4});
  graph.edges.push_back(Edge{3, 4, 5});

  vector<vector<Edge>> forest = prim(graph);

  for (int i = 0; i < forest.size(); i++) {
    for (Edge edge : forest[i]) {
      cout << "(" << i << ", " << edge.dest << ", " << edge.weight << ")" << endl;
    }
  }

  return 0;
}
