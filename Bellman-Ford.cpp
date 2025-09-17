#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int a, b, cost;
};

int n, m, v;
vector<Edge> edges;
const int INF = 1000000000;

void solve()
{
    vector<int> d(n, INF);
    d[v] = 0;
    for (int i = 0; i < n - 1; ++i)
        for (Edge e : edges)
            if (d[e.a] < INF)
                d[e.b] = min(d[e.b], d[e.a] + e.cost);



     cout << "Distances from " << v << ":\n";
    for (int i = 0; i < n; i++) {
        if (d[i] == INF) cout << i << ": INF\n";
        else cout << i << ": " << d[i] << "\n";
    }
}

vector<Edge> generate_graph(int nodes, int edges_count) {
    vector<Edge> g;
    for (int i = 0; i < edges_count; i++) {
        int a = rand() % nodes;
        int b = rand() % nodes;
        if (a == b) continue;
        int cost = (rand() % 101) - 50;
        g.push_back({a, b, cost});
    }
    return g;
}

int main() {
    srand(time(0));

    n = 50;  
    v = 0;  

    for (int test = 1; test <= 10; test++) {
        edges = generate_graph(n, 300);

        cout << edges.size() << endl;
        for (auto &e : edges) {
            cout << e.a << " -> " << e.b << " " << e.cost << endl;
        }
        cout << endl;

        solve();
    }
}
