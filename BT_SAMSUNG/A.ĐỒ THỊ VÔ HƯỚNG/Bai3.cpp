#include <iostream>
#include <vector>

using namespace std;

int countParallelEdges(int V, int E, const vector<pair<int, int>>& edges) {
    vector<vector<int>> adj(V, vector<int>(V, 0));
    for (const auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    int count = 0;
    for (const auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;
        if (adj[u][v] == adj[v][u] == 1) {
            count++;
        }
    }

    return count;
}

int main() {
    int V = 4;
    int E = 5;
    vector<pair<int, int>> edges = {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {0, 2}};

    int result = countParallelEdges(V, E, edges);
    cout << "Số cạnh song song trong đồ thị là: " << result << endl;

    return 0;
}
