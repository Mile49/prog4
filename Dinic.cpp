#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev; 
    int capacity;  
};

class Dinic {
public:
    int numVertices;
    vector<vector<Edge>> adj;
    vector<int> level, iter;

    Dinic(int n) : numVertices(n), adj(n), level(n), iter(n) {}

    void addEdge(int from, int to, int capacity) {
        adj[from].push_back({to, static_cast<int>(adj[to].size()), capacity});
        adj[to].push_back({from, static_cast<int>(adj[from].size()) - 1, 0});
    }

    bool bfs(int source, int sink) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[source] = 0;
        q.push(source);

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (auto &edge : adj[v]) {
                if (edge.capacity > 0 && level[edge.to] < 0) {
                    level[edge.to] = level[v] + 1;
                    q.push(edge.to);
                }
            }
        }
        return level[sink] != -1;
    }

    int dfs(int v, int sink, int flow, vector<int> &path) {
        if (v == sink) {
            path.push_back(sink);
            return flow;
        }

        for (int &i = iter[v]; i < (int)adj[v].size(); i++) {
            Edge &edge = adj[v][i];
            if (edge.capacity > 0 && level[v] < level[edge.to]) {
                int pushed = dfs(edge.to, sink, min(flow, edge.capacity), path);
                if (pushed > 0) {
                    edge.capacity -= pushed;
                    adj[edge.to][edge.rev].capacity += pushed;
                    path.push_back(v);
                    return pushed;
                }
            }
        }
        return 0;
    }

    int maxFlow(int source, int sink) {
        int totalFlow = 0;

        while (bfs(source, sink)) {
            fill(iter.begin(), iter.end(), 0);
            vector<int> path;
            int pushed;

            while ((pushed = dfs(source, sink, INT_MAX, path)) > 0) {
                totalFlow += pushed;
                reverse(path.begin(), path.end());

                cout << "flow " << pushed << ": ";
                for (size_t i = 0; i < path.size(); i++) {
                    cout << path[i];
                    if (i + 1 != path.size()) cout << " -> ";
                }
                cout << "\n";

                path.clear();
            }
        }
        return totalFlow;
    }
};

int main() {
    /*
    int n = 4;
    Dinic graph(n);

    graph.addEdge(0, 1, 8);
    graph.addEdge(0, 2, 8);
    graph.addEdge(2, 1, 1);
    graph.addEdge(2, 3, 8);
    graph.addEdge(1, 3, 8);
    */

    /*
    int n = 8;
    Dinic graph(n);

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
    Dinic graph(n);

    graph.addEdge(0, 2, 5);
    graph.addEdge(0, 3, 3);
    graph.addEdge(1, 4, 99);
    graph.addEdge(2, 3, 2);
    graph.addEdge(2, 1, 3);
    graph.addEdge(2, 4, 99);
    graph.addEdge(3, 1, 6);
    */

    int n = 5;
    Dinic graph(n);

    graph.addEdge(0, 2, 99);
    graph.addEdge(0, 3, 99);
    graph.addEdge(1, 4, 4);
    graph.addEdge(2, 3, 2);
    graph.addEdge(2, 1, 3);
    graph.addEdge(2, 4, 3);
    graph.addEdge(3, 1, 6);

    /*
    int n = 5;
    Dinic graph(n);

    graph.addEdge(0, 2, 99);
    graph.addEdge(0, 3, 3);
    graph.addEdge(2, 3, 2);
    graph.addEdge(2, 1, 3);
    graph.addEdge(2, 4, 3);
    graph.addEdge(1, 4, 99);
    graph.addEdge(3, 1, 6);
    */

    int source = 0, sink = n - 1;
    int maxFlowValue = graph.maxFlow(source, sink);

    cout << maxFlowValue << endl;
    return 0;
}
