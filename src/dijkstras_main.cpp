#include "dijkstras.h"

void call_dijkstra(string file_path) {
    Graph G;
    file_to_graph(file_path, G);
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    for (int i = 0; i < distances.size(); i++) {
        vector<int> path = extract_shortest_path(distances, previous, i);
        print_path(path, distances[i]);
    }
}

int main() {
    cout << "small.txt\n";
    call_dijkstra("/home/ychao13/ICS46/ics-46-hw-9-twleochao/src/small.txt");
    cout << "medium.txt\n";
    call_dijkstra("/home/ychao13/ICS46/ics-46-hw-9-twleochao/src/medium.txt");
    cout << "large.txt\n";
    call_dijkstra("/home/ychao13/ICS46/ics-46-hw-9-twleochao/src/large.txt");
    cout << "largest.txt\n";
    call_dijkstra("/home/ychao13/ICS46/ics-46-hw-9-twleochao/src/largest.txt");

}
