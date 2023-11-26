#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>
#include "graph.h"

using namespace std;

int main() {
    string inputFile;
    cout << "Enter name of graph file: " << endl;
    cin >> inputFile;

    ifstream infile(inputFile);

    unordered_set<string> uniqueVertices;
    vector<tuple<string, string, int>> edges;  // Temporary storage for edges

    string src;
    string dst;
    int cost;

    while (infile >> src >> dst >> cost) {
        uniqueVertices.insert(src);
        uniqueVertices.insert(dst);
        edges.emplace_back(src, dst, cost);
    }

    // Determine the number of vertices based on unique entries
    int totalVertices = static_cast<int>(uniqueVertices.size());

    // Now, you can create the Graph object with the calculated number of vertices
    Graph graph(totalVertices);

    // Insert nodes into the graph
    for (const auto& edge : edges) {
        graph.insertNode(get<0>(edge), get<1>(edge), get<2>(edge));
    }

    cout << "Enter name of starting vertex: " << endl;
    string start;
    cin >> start;

    while (!graph.containsNode(start)) {
        cout << "Enter name of starting vertex: \n";
        cin >> start;
    }

    clock_t t_start = clock();
    graph.DijkstraAlgotithm(start);
    clock_t t_end = clock();
    double time_taken = static_cast<double>(t_end - t_start) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << time_taken << "\n";

    graph.output();

    return 0;
}
