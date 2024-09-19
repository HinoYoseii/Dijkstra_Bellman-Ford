#include <iostream>
#include <vector>
#include <locale.h>

using namespace std;

const int INF = 2147483647;

class Graph {
private:
    int V; // Liczba wierzchołków
    vector<vector<pair<int, int>>> adj; // Wektor przechowujący wektor z parami wierzchołek i waga 

public:
    Graph(int v) {
        this->V = v;
        adj.resize(V);
    }

    // Dodanie krawędzi do grafu
    void addEdge(int u, int v, int weight) {
        adj[u].push_back(make_pair(v, weight));
    }

    // Algorytm Dijkstry
    vector<int> dijkstra(int source) {
        vector<int> dist(V, INF); //odległości
        vector<bool> visited(V, false); //odwiedzone wierzchołki
        dist[source] = 0;

        for (int i = 0; i < V - 1; ++i) {
            int u = -1;
            for (int j = 0; j < V; ++j) {
                if (!visited[j] && (u == -1 || dist[j] < dist[u]))
                    u = j;
            }

            if (dist[u] == INF)
                break;

            visited[u] = true;

            for (const auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;
                if (dist[u] + weight < dist[v])
                    dist[v] = dist[u] + weight;
            }
        }
        return dist;
    }

    // Algorytm Bella-Forda
    vector<int> bellmanFord(int source) {
        vector<int> dist(V, INF); //odległości
        dist[source] = 0;

        for (int i = 0; i < V - 1; ++i) {
            for (int u = 0; u < V; ++u) {
                for (const auto& edge : adj[u]) {
                    int v = edge.first;
                    int weight = edge.second;
                    if (dist[u] != INF && dist[u] + weight < dist[v])
                        dist[v] = dist[u] + weight;
                }
            }
        }

        for (int u = 0; u < V; ++u) {
            for (const auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;
                if (dist[u] != INF && dist[u] + weight < dist[v]) {
                    cout << "Graf zawiera cykl ujemny\n";
                    return {};
                }
            }
        }

        return dist;
    }
};

void printDistances(const vector<int>& distances, int source) {
    for (size_t i = 0; i < distances.size(); ++i) {
        cout << "od " << source << " do " << i << " = ";
        if (distances[i] == INF) {
            cout << "INF\n";
        }
        else {
            cout << distances[i] << "\n";
        }
    }
}

int main() {
    setlocale(0, "POLISH");

    // Dodanie krawędzi do grafu skierowanego ważonego, (wierzchołek A, wierzchołek B, waga)
    Graph A(5);
    A.addEdge(0, 1, 4);
    A.addEdge(0, 2, 7);
    A.addEdge(0, 3, 3);
    A.addEdge(1, 2, 4);
    A.addEdge(1, 3, 5);
    A.addEdge(2, 1, -3);
    A.addEdge(3, 2, 3);
    A.addEdge(3, 4, 2);
    A.addEdge(4, 2, -4);

    Graph B(6);
    B.addEdge(0, 1, 3);
    B.addEdge(0, 2, 5);
    B.addEdge(0, 3, 4);
    B.addEdge(1, 3, 2);
    B.addEdge(2, 4, 2);
    B.addEdge(2, 5, 4);
    B.addEdge(3, 2, 2);
    B.addEdge(3, 4, 5);
    B.addEdge(4, 5, 1);

    Graph C(9);
    C.addEdge(0, 1, 4);
    C.addEdge(0, 2, 4);
    C.addEdge(0, 5, 1);
    C.addEdge(1, 2, 2);
    C.addEdge(2, 3, 6);
    C.addEdge(4, 0, 4);
    C.addEdge(4, 3, -2);
    C.addEdge(5, 1, -1);
    C.addEdge(5, 4, 2);
    C.addEdge(5, 6, 6);
    C.addEdge(5, 7, 3);
    C.addEdge(6, 7, 1);
    C.addEdge(7, 3, 2);
    C.addEdge(7, 8, -2);

    Graph D(9); //z cyklem negatywnym
    D.addEdge(0, 1, 4);
    D.addEdge(0, 2, 4);
    D.addEdge(0, 5, 1);
    D.addEdge(1, 2, 2);
    D.addEdge(2, 3, 6);
    D.addEdge(4, 0, -4);
    D.addEdge(4, 3, -2);
    D.addEdge(5, 1, -1);
    D.addEdge(5, 4, 2);
    D.addEdge(5, 6, 6);
    D.addEdge(5, 7, 3);
    D.addEdge(6, 7, 1);
    D.addEdge(7, 3, 2);
    D.addEdge(7, 8, -2);


    int source = 0; // Wierzchołek źródłowy

    cout << "Graf A\n\n";
    cout << "Dijkstra\n";
    printDistances(A.dijkstra(source), source);
    cout << "\nBellman-Ford\n";
    printDistances(A.bellmanFord(source), source);

    cout << "\n\nGraf B\n\n";
    cout << "Dijkstra\n";
    printDistances(B.dijkstra(source), source);
    cout << "\nBellman-Ford\n";
    printDistances(B.bellmanFord(source), source);

    cout << "\n\nGraf C\n\n";
    cout << "Dijkstra\n";
    printDistances(C.dijkstra(source), source);
    cout << "\nBellman-Ford\n";
    printDistances(C.bellmanFord(source), source);

    cout << "\n\nGraf D\n\n";
    cout << "Dijkstra\n";
    printDistances(D.dijkstra(source), source);
    cout << "\nBellman-Ford\n";
    printDistances(D.bellmanFord(source), source);

    return 0;
}
