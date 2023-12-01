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
    return distance > other.distance;
  }
};

vector<vector<int>> dijkstra(Graph graph, vector<int> sources) {
  // Khởi tạo một rừng các đường đi ngắn nhất.
  vector<vector<int>> paths(graph.numVertices);

  // Khởi tạo một hàng đợi ưu tiên chứa tất cả các đỉnh nguồn.
  priority_queue<Node> queue;
  for (int source : sources) {
    queue.push({source, 0});
  }

  // Khởi tạo một tập hợp các đỉnh đã được duyệt.
  set<int> visited;

  // Lặp lại cho đến khi tất cả các đỉnh đều được duyệt.
  while (!queue.empty()) {
    // Lấy đỉnh có khoảng cách nhỏ nhất ra khỏi hàng đợi ưu tiên.
    Node current = queue.top();
    queue.pop();

    // Nếu đỉnh này đã được duyệt thì bỏ qua.
    if (visited.count(current.vertex)) {
      continue;
    }

    // Đánh dấu đỉnh này là đã được duyệt.
    visited.insert(current.vertex);

    // Thêm cạnh có trọng số 0 nối đỉnh này với tất cả các đỉnh nguồn.
    for (int source : sources) {
      if (current.vertex != source) {
        paths[source].push_back(current.vertex);
      }
    }

    // Duyệt qua các cạnh đi ra từ đỉnh này.
    for (Edge edge : graph.edges) {
      // Nếu đỉnh đích chưa được duyệt thì cập nhật khoảng cách của nó.
      if (!visited.count(edge.dest)) {
        int newDistance = current.distance + edge.weight;
        if (newDistance < paths[edge.dest].size() || paths[edge.dest].empty()) {
          paths[edge.dest].push_back(current.vertex);
          queue.push({edge.dest, newDistance});
        }
      }
    }
  }

  return paths;
}

int main() {
  // Tạo đồ thị.
  Graph graph = Graph{5};
  graph.edges.push_back({0, 1, 1});
  graph.edges.push_back({0, 2, 7});
  graph.edges.push_back({1, 2, 2});
  graph.edges.push_back({1, 3, 4});
  graph.edges.push_back({2, 3, 5});

  // Tạo tập đỉnh nguồn.
  vector<int> sources = {0, 1};

  // Tìm đường đi ngắn nhất từ nguồn bất kì tới mỗi đỉnh.
  vector<vector<int>> paths = dijkstra(graph, sources);

  // In ra đường đi ngắn nhất từ nguồn 0 tới đỉnh 3.
  for (int vertex : paths[0]) {
    cout << vertex << " ";
  }
  cout << endl;

  return 0;
}
