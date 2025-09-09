#include <iostream>
#include <climits>
using namespace std;

#define V 9 

int minDistance(int dist[], bool path[]) {
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < V; v++)
        if (!path[v] && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void printSolution(int dist[]) {
    for (int i = 0; i < V; i++)
        cout << " " << i << " " << dist[i] << endl;
}

void dijkstra(int graph[V][V], int src) {
    int dist[V];    
    bool path[V]; 

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        path[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, path);

        path[u] = true;

        for (int v = 0; v < V; v++)
            if (!path[v] && graph[u][v] &&
                dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    printSolution(dist);
}

int main() {
    return 0;
}
