#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;

// Original had 7 nodes (0-6). Removed nodes 3 and 6, added nodes 5-10 (6 new nodes).
// New graph has 9 nodes (0-8).
const int SIZE = 9;

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
    // Removed original nodes 3 and 6.
    // Added 6 new nodes: 3, 4, 5, 6, 7, 8 (renumbered into a fresh 9-node graph).
    // New edges with updated weights:
    vector<Edge> edges = {
        {0, 1, 8},
        {0, 2, 21},
        {1, 2, 6},
        {1, 3, 5},
        {1, 4, 4},
        {2, 7, 11},
        {2, 8, 8},
        {3, 4, 9},
        {5, 6, 10},
        {5, 7, 15},
        {5, 8, 5},
        {6, 7, 3},
        {6, 8, 7}
    };

    Graph graph(edges);

    graph.printGraph();
    graph.DFS(0);
    graph.BFS(0);

    return 0;
}