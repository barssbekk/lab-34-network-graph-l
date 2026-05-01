#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;

// Original had 7 nodes (0-6), removed nodes 1 and 3, added 6 new nodes
// New graph has 11 nodes (0-10)
const int SIZE = 11;

class Graph {
public:
    vector<vector<Pair>> adjList;

    Graph(vector<Edge> const &edges) {
        adjList.resize(SIZE);
        for (auto &edge : edges) {
            int src    = edge.src;
            int dest   = edge.dest;
            int weight = edge.weight;
            adjList[src].push_back(make_pair(dest, weight));
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    void printGraph() {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < (int)adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }

    void DFS(int start) {
        vector<bool> visited(SIZE, false);
        stack<int> s;

        visited[start] = true;
        s.push(start);

        cout << "DFS starting from vertex " << start << ":" << endl;

        while (!s.empty()) {
            int node = s.top();
            s.pop();
            cout << node << " ";

            for (auto &neighbor : adjList[node]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    s.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }

    void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS starting from vertex " << start << ":" << endl;

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (auto &neighbor : adjList[node]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    q.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    // Removed original nodes 1 and 3.
    // Added 6 new nodes: 5, 6, 7, 8, 9, 10.
    // All new weights.
    vector<Edge> edges = {
        {0, 2, 15},
        {0, 4, 10},
        {2, 4, 7},
        {2, 5, 12},
        {2, 6, 9},
        {4, 7, 5},
        {4, 8, 18},
        {5, 9, 6},
        {5, 6, 11},
        {6, 10, 4},
        {7, 8, 8},
        {8, 9, 14},
        {9, 10, 3},
        {7, 10, 20}
    };

    Graph graph(edges);

    graph.printGraph();
    graph.DFS(0);
    graph.BFS(0);

    return 0;
}