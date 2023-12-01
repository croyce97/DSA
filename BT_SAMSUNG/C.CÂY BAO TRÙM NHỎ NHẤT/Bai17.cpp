#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

class Graph {
private:
    int V;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int vertices) : V(vertices), adj(vertices) {}

    void addEdge(int u, int v, int weight) {
        adj[u].emplace_back(v, weight);
    }

    // Tìm cây bao trùm nhỏ nhất bằng thuật toán Vyssotsky
    vector<int> vyssotskyMST() {
        vector<int> parent(V, -1);
        vector<int> minWeight(V, INF);

        for (int u = 0; u < V; ++u) {
            for (const auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (weight < minWeight[v]) {
                    parent[v] = u;
                    minWeight[v] = weight;
                }
            }
        }

        // Kiểm tra xem có chu trình không
        int cycleVertex = -1;
        for (int u = 0; u < V; ++u) {
            for (const auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (weight < minWeight[v] && parent[v] != u) {
                    // Phát hiện chu trình
                    cycleVertex = v;
                    break;
                }
            }
            if (cycleVertex != -1) {
                break;
            }
        }

        // Nếu không có chu trình, trả về cây bao trùm nhỏ nhất
        if (cycleVertex == -1) {
            return parent;
        }

        // Xác định chu trình và xóa cạnh có trọng số lớn nhất trên chu trình
        vector<bool> visited(V, false);
        vector<bool> inCycle(V, false);

        int current = cycleVertex;
        while (!visited[current]) {
            visited[current] = true;
            inCycle[current] = true;
            current = parent[current];
        }

        int maxWeight = INF;
        int maxWeightEdgeU = -1;
        int maxWeightEdgeV = -1;

        for (int u = 0; u < V; ++u) {
            if (inCycle[u]) {
                for (const auto& edge : adj[u]) {
                    int v = edge.first;
                    int weight = edge.second;

                    if (inCycle[v] && weight < maxWeight) {
                        maxWeight = weight;
                        maxWeightEdgeU = u;
                        maxWeightEdgeV = v;
                    }
                }
            }
        }

        parent[maxWeightEdgeV] = maxWeightEdgeU;

        return parent;
    }
};

int main() {
    // Tạo đồ thị có hướng với trọng số
    Graph graph(5);
    graph.addEdge(0, 1, 2);
    graph.addEdge(1, 2, 1);
    graph.addEdge(2, 0, 3);
    graph.addEdge(1, 3, 4);
    graph.addEdge(3, 4, 5);

    // Tìm cây bao trùm nhỏ nhất
    vector<int> mst = graph.vyssotskyMST();

    // In cây bao trùm nhỏ nhất
    for (int i = 0; i < mst.size(); ++i) {
        if (mst[i] != -1) {
            cout << "Edge: " << mst[i] << " --> " << i << endl;
        }
    }

    return 0;
}
