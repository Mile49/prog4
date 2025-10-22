#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev;
    int capacity;
};

class FordFulkerson {
public:
    const int INF = 1e9;
    int numVertices;
    vector<vector<Edge>> adj;
    vector<bool> visited;

    FordFulkerson(int n) : numVertices(n), adj(n), visited(n) {}

    void addEdge(int from, int to, int capacity) {
        adj[from].push_back({to, static_cast<int>(adj[to].size()), capacity});
        adj[to].push_back({from, static_cast<int>(adj[from].size()) - 1, 0});
    }

    int dfs(int node, int sink, int flow, vector<int>& path) {
        if (node == sink) {
            path.push_back(sink);
            return flow;
        }

        visited[node] = true;
        for (auto& edge : adj[node]) {
            if (!visited[edge.to] && edge.capacity > 0) {
                int pushed = dfs(edge.to, sink, min(flow, edge.capacity), path);
                if (pushed > 0) {
                    edge.capacity -= pushed;
                    adj[edge.to][edge.rev].capacity += pushed;
                    path.push_back(node);
                    return pushed;
                }
            }
        }
        return 0;
    }

    int maxFlow(int source, int sink) {
        int totalFlow = 0;

        while (true) {
            fill(visited.begin(), visited.end(), false);
            vector<int> path;
            int pushed = dfs(source, sink, INF, path);
            if (pushed == 0) break;

            totalFlow += pushed;
            reverse(path.begin(), path.end());

            cout << "flow " << pushed << ": ";
            for (size_t i = 0; i < path.size(); ++i) {
                cout << path[i];
                if (i + 1 != path.size()) cout << " -> ";
            }
            cout << "\n";
        }
        return totalFlow;
    }
};

int main() {
    int n = 5;
    FordFulkerson graph(n);

     /*
    int n = 4;
    FordFulkerson graph(n);

    graph.addEdge(0, 1, 8);
    graph.addEdge(0, 2, 8);
    graph.addEdge(2, 1, 1);
    graph.addEdge(2, 3, 8);
    graph.addEdge(1, 3, 8);
    */

    /*
    int n = 8;
    FordFulkerson graph(n);

    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 1);
    graph.addEdge(0, 3, 1);
    graph.addEdge(1, 4, 1);
    graph.addEdge(1, 5, 1);
    graph.addEdge(1, 6, 1);
    graph.addEdge(2, 5, 1);
    graph.addEdge(3, 5, 1);
    graph.addEdge(4, 7, 1);
    graph.addEdge(5, 7, 1);
    graph.addEdge(6, 7, 1);
    */

    /*
    int n = 5;
    FordFulkerson graph(n);

    graph.addEdge(0, 2, 5);
    graph.addEdge(0, 3, 3);
    graph.addEdge(1, 4, 99);
    graph.addEdge(2, 3, 2);
    graph.addEdge(2, 1, 3);
    graph.addEdge(2, 4, 99);
    graph.addEdge(3, 1, 6);
    */

    /*
    int n = 5;
    FordFulkerson graph(n);

    graph.addEdge(0, 2, 99);
    graph.addEdge(0, 3, 99);
    graph.addEdge(1, 4, 4);
    graph.addEdge(2, 3, 2);
    graph.addEdge(2, 1, 3);
    graph.addEdge(2, 4, 3);
    graph.addEdge(3, 1, 6);
    */
    graph.addEdge(0, 2, 99);
    graph.addEdge(0, 3, 3);
    graph.addEdge(2, 3, 2);
    graph.addEdge(2, 1, 3);
    graph.addEdge(2, 4, 3);
    graph.addEdge(1, 4, 99);
    graph.addEdge(3, 1, 6);

    int source = 0, sink = n - 1;
    int maxFlow = graph.maxFlow(source, sink);

    cout << maxFlow << endl;
    return 0;
}
