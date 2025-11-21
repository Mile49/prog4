#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int n;
vector<vector<int>> capacity, flow;
vector<int> height, excess, seen;
vector<vector<int>> adj;

void add_edge(int u, int v, int cap) {
    capacity[u][v] = cap;
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void push(int u, int v) {
    int send = min(excess[u], capacity[u][v] - flow[u][v]);
    if (send > 0 && height[u] == height[v] + 1) {
        flow[u][v] += send;
        flow[v][u] -= send;
        excess[u] -= send;
        excess[v] += send;
    }
}

void relabel(int u) {
    int d = INF;
    for (int v : adj[u]) {
        if (capacity[u][v] - flow[u][v] > 0)
            d = min(d, height[v]);
    }
    if (d < INF)
        height[u] = d + 1;
}

void discharge(int u) {
    while (excess[u] > 0) {
        if (seen[u] == adj[u].size()) {
            relabel(u);
            seen[u] = 0;
        } else {
            int v = adj[u][seen[u]];
            if (capacity[u][v] - flow[u][v] > 0 &&
                height[u] == height[v] + 1)
                push(u, v);
            else
                seen[u]++;
        }
    }
}

int max_flow(int s, int t) {
    height.assign(n, 0);
    excess.assign(n, 0);
    seen.assign(n, 0);

    flow.assign(n, vector<int>(n, 0));

    height[s] = n;

    for (int v : adj[s]) {
        flow[s][v] = capacity[s][v];
        flow[v][s] = -capacity[s][v];
        excess[v] = capacity[s][v];
        excess[s] -= capacity[s][v];
    }

    queue<int> Q;
    for (int i = 0; i < n; i++)
        if (i != s && i != t && excess[i] > 0)
            Q.push(i);

    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        int old_height = height[u];
        discharge(u);
        if (height[u] > old_height)
            Q.push(u);
    }

    int maxflow = 0;
    for (int v : adj[s]) maxflow += flow[s][v];
    return maxflow;
}

int main() {
    cin >> n;
    capacity.assign(n, vector<int>(n, 0));
    adj.assign(n, vector<int>());

    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        add_edge(u, v, c);
    }

    int s, t;
    cin >> s >> t;

    cout << "Output: " << max_flow(s, t) << "\n";
}
