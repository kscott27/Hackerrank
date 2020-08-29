#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <deque>
using namespace std;

class Graph {
public:
  Graph(int n) : adj_(n), n_(n) {}

  void add_edge(int u, int v) {
    adj_[u].push_back(v);
    adj_[v].push_back(u);
  }

  vector<int> shortest_reach(int start) {
    vector<int> result(n_, -1);
    // The queue consists of 2 idx vectors.
    // idx 0: the value of the node
    // idx 1: the current distance from the start
    deque<vector<int>> q;
    // Used to ensure we don't revisit nodes during
    // the traversal.
    vector<bool> visited(n_, false);
    // The starting node has distance 0 from itself.
    q.push_back({start, 0});
    // Traverse until there are no more items on the queue.
    while( q.size() > 0 ) {
      vector<int> current = q.front();
      // Grab all adjacent nodes to the current node by
      // indexing into the adjaceny list.
      vector<int> connections = adj_[current[0]];
      for( auto c : connections ) {
        // Only push nodes onto the queue if they have not been visited.
        if( !visited[c] ) {
          q.push_back({c, current[1] + 6});
          visited[c] = true;
        }
      }
      // Update the result vector by indexing in via value
      // and setting the distance from the start.
      result[current[0]] = current[1];
      // Current node served its purpose.
      q.pop_front();
    }
    return result;
  }
private:
  vector<vector<int>> adj_; // Adjacency list for mapping the graph
  int n_; // Total number of nodes
};

int main() {
    int queries;
    cin >> queries;
        
    for (int t = 0; t < queries; t++) {
      
    int n, m;
        cin >> n;
        // Create a graph of size n where each edge weight is 6: 
        Graph graph(n);
        cin >> m;
        // read and set edges
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            // add each edge to the graph
            graph.add_edge(u, v);
        }
    int startId;
        cin >> startId;
        startId--;
        // Find shortest reach from node s
        vector<int> distances = graph.shortest_reach(startId);

        for (int i = 0; i < distances.size(); i++) {
            if (i != startId) {
                cout << distances[i] << " ";
            }
        }
        cout << endl;
    }
    
    return 0;
}
