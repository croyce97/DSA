#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Graph {
private:
    int V;
    vector<unordered_set<int>> adjList;

public:
    Graph(int vertices) : V(vertices), adjList(vertices) {}

    void addEdge(int u, int v) {
        adjList[u].insert(v);
        adjList[v].insert(u);
    }

    bool isEdgeConnected() {
        for (int i = 0; i < V; ++i) {
            for (int neighbor : adjList[i]) {
                adjList[i].erase(neighbor);
                adjList[neighbor].erase(i);
                vector<bool> visited(V, false);
                DFS(0, visited);
                addEdge(i, neighbor);
                if (count(visited.begin(), visited.end(), true) < V) {
                    return false;
                }
            }
        }
        return true;
    }

    void DFS(int vertex, vector<bool>& visited) {
        visited[vertex] = true;
        for (int neighbor : adjList[vertex]) {
            if (!visited[neighbor]) {
                DFS(neighbor, visited);
            }
        }
    }
};

int main() {
    int V = 5;
    Graph graph(V);

    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);
    graph.addEdge(1, 3);
    graph.addEdge(3, 4);

    bool isConnected = graph.isEdgeConnected();

    if (isConnected) {
        cout << "Đồ thị có tính chất liên thông cạnh." << endl;
    } else {
        cout << "Đồ thị không có tính chất liên thông cạnh." << endl;
    }

    return 0;
}
