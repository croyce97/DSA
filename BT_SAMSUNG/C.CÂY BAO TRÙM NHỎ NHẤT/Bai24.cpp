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

vector<Edge> boruvka(Graph graph) {
  // Khởi tạo một rừng gồm các cây đơn lẻ.
  vector<list<int>> forest(graph.numVertices);

  // Lặp lại cho đến khi chỉ còn một cây.
  while (forest.size() > 1) {
    // Tìm cạnh có trọng số nhỏ nhất nối hai cây khác nhau.
    int minWeight = INT_MAX;
    int src = -1;
    int dest = -1;
    for (int i = 0; i < graph.edges.size(); i++) {
      if (forest[graph.edges[i].src] != forest[graph.edges[i].dest]) {
        if (graph.edges[i].weight < minWeight) {
          minWeight = graph.edges[i].weight;
          src = graph.edges[i].src;
          dest = graph.edges[i].dest;
        }
      }
    }

    // Merge hai cây chứa đỉnh src và đỉnh dest.
    // Đầu tiên, tìm đỉnh đầu tiên của cây chứa đỉnh src.
    int srcHead = forest[src].front();

    // Tiếp theo, tìm đỉnh đầu tiên của cây chứa đỉnh dest.
    int destHead = forest[dest].front();

    // Cuối cùng, chèn đỉnh destHead vào cuối cây chứa đỉnh src.
    forest[src].push_back(destHead);

    // Thêm cạnh có trọng số min vào cây bao trùm.
    edges.push_back(Edge{src, dest, minWeight});
  }

  return edges;
}

int main() {
  Graph graph = Graph{5};
  graph.edges.push_back(Edge{0, 1, 1});
  graph.edges.push_back(Edge{0, 2, 7});
  graph.edges.push_back(Edge{1, 3, 2});
  graph.edges.push_back(Edge{2, 3, 4});
  graph.edges.push_back(Edge{3, 4, 5});

  vector<Edge> tree = boruvka(graph);

  for (Edge edge : tree) {
    cout << "(" << edge.src << ", " << edge.dest << ", " << edge.weight << ")" << endl;
  }

  return 0;
}
