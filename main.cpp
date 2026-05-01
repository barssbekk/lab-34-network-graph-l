// COMSC-210 | Lab 34 | Barsbek
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <climits>

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

    void dijkstra(int start) {
        vector<int> dist(SIZE, INT_MAX);
        dist[start] = 0;

        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        pq.push(make_pair(0, start));

        while (!pq.empty()) {
            int currDist = pq.top().first;
            int currNode = pq.top().second;
            pq.pop();

            if (currDist > dist[currNode])
                continue;

            for (auto &neighbor : adjList[currNode]) {
                int nextNode   = neighbor.first;
                int edgeWeight = neighbor.second;

                if (dist[currNode] + edgeWeight < dist[nextNode]) {
                    dist[nextNode] = dist[currNode] + edgeWeight;
                    pq.push(make_pair(dist[nextNode], nextNode));
                }
            }
        }

        cout << "Shortest path from " << locationNames[start] << ":" << endl;
        cout << "========================================" << endl;
        for (int i = 0; i < SIZE; i++) {
            cout << locationNames[start] << " -> " << locationNames[i] << " : ";
            if (dist[i] == INT_MAX)
                cout << "No path" << endl;
            else
                cout << dist[i] << " miles" << endl;
        }
        cout << endl;
    }

    void primMST() {
        vector<bool> inMST(SIZE, false);
        vector<int> key(SIZE, INT_MAX);
        vector<int> parent(SIZE, -1);

        key[0] = 0;

        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        pq.push(make_pair(0, 0));

        while (!pq.empty()) {
            int currNode = pq.top().second;
            pq.pop();

            inMST[currNode] = true;

            for (auto &neighbor : adjList[currNode]) {
                int nextNode   = neighbor.first;
                int edgeWeight = neighbor.second;

                if (!inMST[nextNode] && edgeWeight < key[nextNode]) {
                    key[nextNode]    = edgeWeight;
                    parent[nextNode] = currNode;
                    pq.push(make_pair(key[nextNode], nextNode));
                }
            }
        }

        cout << "Minimum Spanning Tree edges:" << endl;
        cout << "============================" << endl;
        int totalWeight = 0;
        for (int i = 1; i < SIZE; i++) {
            if (parent[i] != -1) {
                cout << "Edge from " << locationNames[parent[i]]
                     << " to " << locationNames[i]
                     << " with distance: " << key[i] << " miles" << endl;
                totalWeight += key[i];
            }
        }
        cout << "Total MST distance: " << totalWeight << " miles" << endl;
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

    int choice;
    do {
        cout << "City Road Network Menu:" << endl;
        cout << "[1] Display city road network" << endl;
        cout << "[2] Road inspection route (DFS)" << endl;
        cout << "[3] Emergency response coverage (BFS)" << endl;
        cout << "[4] Calculate shortest paths" << endl;
        cout << "[5] Find minimum spanning tree" << endl;
        cout << "[0] Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1:
                graph.printGraph();
                break;
            case 2:
                graph.DFS(0);
                break;
            case 3:
                graph.BFS(0);
                break;
            case 4:
                graph.dijkstra(0);
                break;
            case 5:
                graph.primMST();
                break;
            case 0:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl << endl;
        }
    } while (choice != 0);

    return 0;
}