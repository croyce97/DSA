#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adj;

public:
    Graph(int vertices) : V(vertices), adj(vertices) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    bool isUniqueTopologicalOrder() {
        // Đếm bậc vào của mỗi đỉnh
        vector<int> inDegree(V, 0);
        for (int i = 0; i < V; ++i) {
            for (int neighbor : adj[i]) {
                inDegree[neighbor]++;
            }
        }

        // Đếm số đỉnh có bậc vào là 0
        int countZeroInDegree = 0;
        for (int i = 0; i < V; ++i) {
            if (inDegree[i] == 0) {
                countZeroInDegree++;
            }
        }

        // Kiểm tra xem có đúng một đỉnh có bậc vào là 0 không
        if (countZeroInDegree == 1) {
            // Sử dụng BFS để kiểm tra mỗi cặp đỉnh liên tiếp có cạnh kết nối không
            unordered_set<int> visited;
            queue<int> q;

            // Tìm đỉnh có bậc vào là 0
            int startVertex = 0;
            for (int i = 0; i < V; ++i) {
                if (inDegree[i] == 0) {
                    startVertex = i;
                    break;
                }
            }

            q.push(startVertex);
            visited.insert(startVertex);

            while (!q.empty()) {
                int current = q.front();
                q.pop();

                for (int neighbor : adj[current]) {
                    if (visited.find(neighbor) == visited.end()) {
                        q.push(neighbor);
                        visited.insert(neighbor);
                    }
                }
            }

            // Kiểm tra xem tất cả các đỉnh đã được duyệt hay chưa
            return visited.size() == V;
        }

        return false;
    }
};

int main() {
    // Tạo đồ thị có hướng
    Graph graph(5);
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);

    // Kiểm tra xem có thứ tự tô pô duy nhất hay không
    if (graph.isUniqueTopologicalOrder()) {
        cout << "Do thi co thu tu to po duy nhat." << endl;
    } else {
        cout << "Do thi khong co thu tu to po duy nhat." << endl;
    }

    return 0;
}
