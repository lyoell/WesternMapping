#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <list>
#include <map>
#include <algorithm>

class Edge {
public:
    int destination;
    double weight;
    std::string description;

    //Constructor
    Edge(int dest, double w, const std::string& desc) : destination(dest), weight(w), description(desc) {}
};

// Class representing a graph
class Graph {
private:
    int vertices;
    std::vector<std::vector<Edge>> adjacencyList; // Use vector of Edge objects

public:
    // Constructor to initialize the graph with a given number of vertices
    Graph(int v) : vertices(v), adjacencyList(v) {}

    std::map<int, std::pair<double, std::string>> shortestPathFromSource;

    // Function to add an undirected edge between vertices u and v with a given weight and description
    void addEdge(int u, int v, double weight, const std::string& description) {
        adjacencyList[u].emplace_back(v, weight, description);
        adjacencyList[v].emplace_back(u, weight, description); // Assuming an undirected graph
    }


    // Dijkstra's algorithm for finding the shortest path from a source to a destination
    void dijkstra(int source) {
        std::list<int> Nprime = {source};

        // Initialize shortestPathFromSource with appropriate values
        for (int c = 0; c < adjacencyList.size(); c++) {
            if (c == source) {
                shortestPathFromSource[c] = std::make_pair(0.0, "");
            } else {
                shortestPathFromSource[c] = std::make_pair(std::numeric_limits<double>::infinity(), "");
            }
        }

        while (Nprime.size() < adjacencyList.size()) {
            // Finding the node with the minimum distance value
            double minValue = std::numeric_limits<double>::max();
            int minIndex = 0;

            for (int c = 0; c < adjacencyList.size(); c++) {
                int currentKey = c;
                double currentValue = shortestPathFromSource[c].first;

                // Skip if already in Nprime
                if (std::find(Nprime.begin(), Nprime.end(), currentKey) != Nprime.end()) {
                    continue;
                }

                if (currentValue < minValue) {
                    minValue = currentValue;
                    minIndex = currentKey;
                }
            }

            int node = minIndex;
            Nprime.emplace_back(node);

            // Update shortestPathFromSource for neighbors of the current node
            for (int c = 0; c < adjacencyList.size(); c++) {
                if (c == source || std::find(Nprime.begin(), Nprime.end(), c) != Nprime.end()) {
                    continue;
                }

                std::pair<double, std::string> tempEdge = findEdge(node, c);

                // Update shortestPathFromSource considering the distance from the current node to the neighbor
                if (tempEdge.first + shortestPathFromSource[node].first < shortestPathFromSource[c].first) {
                    shortestPathFromSource[c] = std::make_pair(tempEdge.first + shortestPathFromSource[node].first,
                                                               shortestPathFromSource[node].second + (shortestPathFromSource[node].second.empty() ? "" : ",") + tempEdge.second);
                }
            }
        }
    }

    std::pair<double, std::string> findEdge(int u, int v) const {
        for (const auto& edge : adjacencyList[u]) {
            if (edge.destination == v) {
                // Edge with destination vertex v found
                return {edge.weight, edge.description};
            }
        }

        // Edge with destination vertex v not found
        return {std::numeric_limits<double>::infinity(), ""}; // You can choose an appropriate default value
    }

};


// Main function
int main() {
    // Create a graph with 30 vertices
    Graph graph(30);

    // Add edges to the graph with double weights
    graph.addEdge(0, 1, 0.25, "Walk between XXX Kininvie and Sarnia ");
    graph.addEdge(0, 3, 0.65, "Walk between XXX Kininvie and Brescia Parking lot");
    graph.addEdge(1, 2, 0.8, "Walk between Sarnia and the Subway + 711 lights");
    graph.addEdge(2, 5, 0.35, "Walk between Western road lights and the  Rec center Western Road");
    graph.addEdge(2, 12, 0.53, " Walk between the Western Road lights and  the Health Sci building area on Philip Aziz");
    graph.addEdge(3, 4, 0.36, "Walk between the lights on Brescia Lane x Western and the Brescia Parking lot");
    graph.addEdge(3, 6, 0.38, "Walk between the Brescia parking lot and the Huron underpass ");
    graph.addEdge(4, 5, 0.37, "Walk between the Brescia Lane x Western lights and the rec center Western Road area");
    graph.addEdge(4, 6, 0.31, "Walk between the Brescia Lane x Western lights and the Huron underpass");
    graph.addEdge(4, 10, 0.25, "Walk between the Brescia Lane x Western Lights and the Alumni Roundabout");
    graph.addEdge(5, 11, 0.11, "Walk between the Western Rec parking area and the Western Rec entrance");
    graph.addEdge(6, 7, 0.29, "Walk between the Huron Underpass and the Elgin Drive exit to Western Road");
    graph.addEdge(6, 9, 0.22, "Walk between the Huron Underpass and the footpath in front of the UCC");
    graph.addEdge(7, 8, 0.27, "Walk between the Elgin Drive exit at Western Road and the footpath by Social Sci");
    graph.addEdge(8, 9, 0.18, "Walk between the footpath by Social Sci and the footpath in front of the UCC");
    graph.addEdge(8, 9, 0.18, "Walk between the footpath by Social Sci and the footpath in front of the UCC");
    graph.addEdge(8,19,0.18,"Walk between the footpath by Nat Sci and the UC hill footpath.");
    graph.addEdge(8,21,0.19,"Walk between the footpath by Nat Sci and Nat Sci physics building.");
    graph.addEdge(9,14,0.13,"Walk between the footpath by UCC and the UC hill parking lot.");
    graph.addEdge(9,10,0.27,"Walk between the footpath by UCC and the Alumni Roundabout.");
    graph.addEdge(10,11,0.28,"Walk between the Alumni Roundabout and the Rec Center entrance.");
    graph.addEdge(10,13,0.15,"Walk between the Alumni Roundabout and the parking lot entrance for the UC hill parking lot.");
    graph.addEdge(11,12,0.29,"Walk between the Rec Center entrance and the Health Sci building area.");
    graph.addEdge(12,16,0.14,"Walk between the Health Sci building area and the stop sign by the music building.");
    graph.addEdge(13,14,0.18,"Walk between the entrance for the UC hill parking lot and the exit of that parking lot to UC hill.");
    graph.addEdge(13,15,0.11,"Walk between the entrance for the UC hill parking lot and the music building footpath.");
    graph.addEdge(14,17,0.18,"Walk between the top of UC hill and the bottom of UC hill.");
    graph.addEdge(14,19,0.16,"Walk between the top of UC hill near the UCC and the top of UC hill near the physics building.");
    graph.addEdge(15,16,0.03,"Walk between the UC footpath at Music building and the stop sign there.");
    graph.addEdge(15,17,0.18,"Walk between the top of UC hill near the UCC and the top of UC hill near the physics building.");
    graph.addEdge(16,18,0.33,"");
    graph.addEdge(17,18,0.43,"");
    graph.addEdge(18,20,0.32,"");
    graph.addEdge(18,22,0.45,"");
    graph.addEdge(19,20,0.08,"");
    graph.addEdge(20,21,0.12,"");
    graph.addEdge(22,23,0.28,"");
    graph.addEdge(22,24,0.1,"");
    graph.addEdge(23,26,0.27,"");
    graph.addEdge(24,25,0.42,"");
    graph.addEdge(24,29,0.3,"");
    graph.addEdge(25,28,0.17,"");
    graph.addEdge(25,26,0.12,"");
    graph.addEdge(26,27,0.21,"");
    graph.addEdge(27,28,0.14,"");
    graph.addEdge(28,29,0.16,"");


    // Specify source and destination vertices
    int source = 0;

    int destination;

    // Prompt the user for input and read
    std::cout << "Enter your destination: ";
    std::cin >> destination;
    graph.dijkstra(source);
    std::map<int, std::pair<double, std::string>> map = graph.shortestPathFromSource;


    // Print the shortest path and distance
    std::cout << map[destination].first <<" "<< map[destination].second<< std::endl;

    return 0;
}
