#include <bits/stdc++.h>
using namespace std;

int bfsFindFlow(int start, int sink, vector<int>& parentNode,
                const vector<vector<int>>& graph,
                vector<vector<int>>& capacity)
{
    fill(parentNode.begin(), parentNode.end(), -1);
    parentNode[start] = -2;
    queue<pair<int,int>> q;
    q.push({start, INT_MAX});

    while (!q.empty()) {
        int u = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : graph[u]) {
            if (parentNode[next] == -1 && capacity[u][next] > 0) {
                parentNode[next] = u;
                int newFlow = min(flow, capacity[u][next]);
                if (next == sink) return newFlow;
                q.push({next, newFlow});
            }
        }
    }
    return 0;
}

int maxFlowEdmondsKarp(int nodeCount, int source, int sink,
                       const vector<vector<int>>& graph,
                       vector<vector<int>> capacity)
{
    int totalFlow = 0;
    vector<int> parent(nodeCount);
    int currFlow;

    while ((currFlow = bfsFindFlow(source, sink, parent, graph, capacity))) {
        totalFlow += currFlow;
        int curr = sink;
        while (curr != source) {
            int prev = parent[curr];
            capacity[prev][curr] -= currFlow;
            capacity[curr][prev] += currFlow;
            curr = prev;
        }
    }
    return totalFlow;
}

int main() {
    int nodes, edgesCount, source, sink;
    cin >> nodes >> edgesCount >> source >> sink;

    vector<vector<int>> graph(nodes);
    vector<vector<int>> capacity(nodes, vector<int>(nodes, 0));
    vector<tuple<int,int,int>> edgeList;

    for (int i = 0; i < edgesCount; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back(b);
        graph[b].push_back(a);
        capacity[a][b] = c;
        edgeList.emplace_back(a, b, c);
    }

    int minFlow = INT_MAX;
    pair<int,int> criticalEdge;

    for (auto edge : edgeList) {
    int a = get<0>(edge);
    int b = get<1>(edge);

    auto tempCap = capacity;
    tempCap[a][b] = 0;


        int newFlow = maxFlowEdmondsKarp(nodes, source, sink, graph, tempCap);
        if (newFlow < minFlow) {
            minFlow = newFlow;
            criticalEdge = {a, b};
        }
    }

    cout << criticalEdge.first << " -> " << criticalEdge.second << endl;
    cout << minFlow << endl;
}
