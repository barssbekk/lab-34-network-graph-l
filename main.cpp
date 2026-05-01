#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;

const int SIZE = 7;

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
    vector<Edge> edges = {
        {0, 1, 12}, {0, 2, 8}, {0, 3, 21},
        {2, 3, 6},  {2, 6, 2}, {5, 6, 6},
        {4, 5, 9},  {2, 4, 4}, {2, 5, 5}
    };

    Graph graph(edges);

    graph.printGraph();
    graph.DFS(0);
    graph.BFS(0);

    return 0;
}