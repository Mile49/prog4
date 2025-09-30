#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e12;

vector<vector<long long>> floydWarshall(const vector<vector<long long>> &inputMatrix, int numNodes) {
    auto dist = inputMatrix;

    for (int k = 0; k < numNodes; k++) {
        for (int i = 0; i < numNodes; i++) {
            for (int j = 0; j < numNodes; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    return dist;
}

long long computeTotalCost(const vector<vector<long long>> &dist, int numNodes, long long limitValue, long long INF) {
    long long total = 0;
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            total += (dist[i][j] >= INF ? limitValue : dist[i][j]);
        }
    }
    return total;
}

int main() {
    int numNodes, numEdges;
    long long limitValue;
    cin >> numNodes >> numEdges >> limitValue;

    vector<vector<long long>> adjMatrix(numNodes, vector<long long>(numNodes, INF));
    vector<tuple<int, int, long long>> edgeList;

    for (int i = 0; i < numNodes; i++) {
        adjMatrix[i][i] = 0;
    }

    for (int i = 0; i < numEdges; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        u--;
        v--;
        adjMatrix[u][v] = min(adjMatrix[u][v], w);
        adjMatrix[v][u] = min(adjMatrix[v][u], w);
        edgeList.push_back({u, v, w});
    }

    auto shortestDist = floydWarshall(adjMatrix, numNodes);

    long long baseCost = computeTotalCost(shortestDist, numNodes, limitValue, INF);
    long long maxPossibleCost = baseCost;

    for (auto &edge : edgeList) {
        int u, v;
        long long w;
        tie(u, v, w) = edge;

        auto modifiedMatrix = adjMatrix;
        modifiedMatrix[u][v] = modifiedMatrix[v][u] = limitValue;

        auto newDist = floydWarshall(modifiedMatrix, numNodes);
        long long newCost = computeTotalCost(newDist, numNodes, limitValue, INF);
        maxPossibleCost = max(maxPossibleCost, newCost);
    }

    cout << baseCost << " " << maxPossibleCost << endl;
    return 0;
}
