#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

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

    void DFS(int vertex, vector<bool>& visited, stack<int>& st) {
        visited[vertex] = true;
        for (int neighbor : adj[vertex]) {
            if (!visited[neighbor]) {
                DFS(neighbor, visited, st);
            }
        }
        st.push(vertex);
    }

    void reverseGraph() {
        vector<vector<int>> reversedAdj(V);
        for (int i = 0; i < V; ++i) {
            for (int neighbor : adj[i]) {
                reversedAdj[neighbor].push_back(i);
            }
        }
        adj = reversedAdj;
    }

    void DFSForSCC(int vertex, vector<bool>& visited, vector<int>& scc, int sccNumber) {
        visited[vertex] = true;
        scc[vertex] = sccNumber;
        for (int neighbor : adj[vertex]) {
            if (!visited[neighbor]) {
                DFSForSCC(neighbor, visited, scc, sccNumber);
            }
        }
    }

    void KosarajuAlgorithm() {
        stack<int> st;
        vector<bool> visited(V, false);

        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                DFS(i, visited, st);
            }
        }

        reverseGraph();

        fill(visited.begin(), visited.end(), false);

        int sccNumber = 0;

        while (!st.empty()) {
            int vertex = st.top();
            st.pop();

            if (!visited[vertex]) {
                vector<int> scc(V, -1);
                DFSForSCC(vertex, visited, scc, sccNumber);

                cout << "Strongly Connected Component " << sccNumber << ": ";
                for (int i = 0; i < V; ++i) {
                    if (scc[i] == sccNumber) {
                        cout << i << " ";
                    }
                }
                cout << endl;

                sccNumber++;
            }
        }
    }
};

int main() {
    Graph graph(5);
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);
    graph.addEdge(1, 3);
    graph.addEdge(3, 4);
    graph.KosarajuAlgorithm();

    return 0;
}
