#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

int main() {
    int INF = 1e9;
    int vertices, edgesCount;
    cin >> vertices >> edgesCount;

    vector<tuple<int, int, int>> edgeList;

    for (int i = 0; i < edgesCount; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        edgeList.push_back(make_tuple(from, to, weight));
    }

    vector<vector<int>> dist(vertices, vector<int>(vertices, INF));

    for (int i = 0; i < vertices; i++) {
        dist[i][i] = 0;
    }

    for (size_t i = 0; i < edgeList.size(); i++) {
        int from = get<0>(edgeList[i]);
        int to = get<1>(edgeList[i]);
        int weight = get<2>(edgeList[i]);
        dist[from][to] = weight;
    }

    for (int k = 0; k < vertices; k++) {
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (dist[i][j] == INF) cout << "INF ";
            else cout << dist[i][j] << " ";
        }
        cout << "\n";
    }
}
