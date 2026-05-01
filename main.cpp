#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>

using namespace std;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;

const int SIZE = 11;

string locationNames[SIZE] = {
    "City Hall",          // 0
    "Central Park",       // 1
    "Main Library",       // 2
    "Police Station",     // 3
    "Fire Department",    // 4
    "Hospital",           // 5
    "Shopping Mall",      // 6
    "Train Station",      // 7
    "Airport",            // 8
    "University",         // 9
    "Sports Arena"        // 10
};

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
        cout << "City Road Network:" << endl;
        cout << "==================" << endl;
        for (int i = 0; i < (int)adjList.size(); i++) {
            cout << locationNames[i] << " connects to:" << endl;
            for (Pair v : adjList[i])
                cout << "  -> " << locationNames[v.first]
                     << " (Distance: " << v.second << " miles)" << endl;
        }
        cout << endl;
    }

    void DFS(int start) {
        vector<bool> visited(SIZE, false);
        stack<int> s;

        visited[start] = true;
        s.push(start);

        cout << "Road Inspection Route (DFS) starting from " << locationNames[start] << ":" << endl;
        cout << "Purpose: Inspecting all roads reachable from origin" << endl;
        cout << "=====================================================" << endl;

        while (!s.empty()) {
            int node = s.top();
            s.pop();
            cout << "Visiting: " << locationNames[node] << endl;

            for (auto &neighbor : adjList[node]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    cout << "  -> Road to " << locationNames[neighbor.first]
                         << " (" << neighbor.second << " miles)" << endl;
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

        cout << "Emergency Response Coverage (BFS) starting from " << locationNames[start] << ":" << endl;
        cout << "Purpose: Finding all locations reachable layer by layer" << endl;
        cout << "========================================================" << endl;

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << "Checking: " << locationNames[node] << endl;

            for (auto &neighbor : adjList[node]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    cout << "  -> Next stop: " << locationNames[neighbor.first]
                         << " (" << neighbor.second << " miles)" << endl;
                    q.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }
};

int main() {
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