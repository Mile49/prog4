#include <iostream>
#include <vector>

using namespace std;

class AdjGraph {
    private:
        int V;
        vector<vector<int>> adj;

    public:
        AdjGraph(int V) {
            this->V = V;
            adj.resize(V);
        }

        void addEdge(int u, int v){
            adj[u].push_back(v);
        }

        void printAdjGraph() {
            for (int i = 0; i < V; ++i) {
                for (int v : adj[i])
                    cout << v << " ";
                cout << endl;
            }
        }
};

class MxGraph {
    private:
        int V;
        vector<vector<int>> matrix;

    public:
        MxGraph(int V) {
            this->V = V;
            matrix.resize(V, vector<int>(V, 0));
        }

        void addEdge(int u, int v) {
            matrix[u][v] = 1;
        }

        void printMxGraph() {
            for (int i = 0; i < V; ++i) {
                for (int j = 0; j < V; ++j) {
                    cout << matrix[i][j] << " ";
                }
                cout << endl;
            }
        }
};

int main() {


    return 0;
}