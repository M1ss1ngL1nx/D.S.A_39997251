#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;

// ============================================================================
// ABSTRACT DATA TYPE: GRAPH (using Adjacency List)
// ============================================================================
// A Graph is a collection of nodes (vertices) connected by edges.
// Can be directed or undirected, weighted or unweighted.
// Adjacency list representation: uses linked lists for efficient storage.
// Time Complexity:
//   - Add Vertex: O(1)
//   - Add Edge: O(1)
//   - Remove Edge: O(degree of vertex)
//   - DFS: O(V + E)
//   - BFS: O(V + E)
// Space: O(V + E)
// ============================================================================

template <typename T>
class Graph {
private:
    // Adjacency list: maps each vertex to its list of adjacent vertices
    unordered_map<T, list<T>> adjacencyList;

public:
    // Add a vertex to the graph
    void addVertex(T vertex) {
        if (adjacencyList.find(vertex) == adjacencyList.end()) {
            adjacencyList[vertex] = list<T>();
        }
    }

    // Add an undirected edge between two vertices
    void addEdge(T u, T v) {
        // Ensure both vertices exist
        addVertex(u);
        addVertex(v);
        
        // Add edge from u to v
        adjacencyList[u].push_back(v);
        
        // Add edge from v to u (for undirected graph)
        adjacencyList[v].push_back(u);
    }

    // Add a directed edge from u to v
    void addDirectedEdge(T u, T v) {
        addVertex(u);
        addVertex(v);
        adjacencyList[u].push_back(v);
    }

    // Remove an edge between two vertices
    void removeEdge(T u, T v) {
        if (adjacencyList.find(u) != adjacencyList.end()) {
            adjacencyList[u].remove(v);
        }
        if (adjacencyList.find(v) != adjacencyList.end()) {
            adjacencyList[v].remove(u);
        }
    }

    // Get list of adjacent vertices
    list<T> getAdjacent(T vertex) {
        if (adjacencyList.find(vertex) != adjacencyList.end()) {
            return adjacencyList[vertex];
        }
        return list<T>();
    }

    // Check if vertex exists
    bool hasVertex(T vertex) {
        return adjacencyList.find(vertex) != adjacencyList.end();
    }

    // Check if edge exists
    bool hasEdge(T u, T v) {
        if (adjacencyList.find(u) == adjacencyList.end()) {
            return false;
        }
        for (T neighbor : adjacencyList[u]) {
            if (neighbor == v) {
                return true;
            }
        }
        return false;
    }

    // Depth-First Search starting from a vertex
    // DFS uses a stack and explores as far as possible along each branch
    void dfs(T startVertex) {
        unordered_map<T, bool> visited;
        stack<T> st;
        
        st.push(startVertex);
        visited[startVertex] = true;
        
        cout << "DFS: ";
        while (!st.empty()) {
            T vertex = st.top();
            st.pop();
            cout << vertex << " ";
            
            // Visit all unvisited adjacent vertices
            for (T neighbor : adjacencyList[vertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    st.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    // Breadth-First Search starting from a vertex
    // BFS uses a queue and explores vertices level by level
    void bfs(T startVertex) {
        unordered_map<T, bool> visited;
        queue<T> q;
        
        q.push(startVertex);
        visited[startVertex] = true;
        
        cout << "BFS: ";
        while (!q.empty()) {
            T vertex = q.front();
            q.pop();
            cout << vertex << " ";
            
            // Visit all unvisited adjacent vertices
            for (T neighbor : adjacencyList[vertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    // Print the adjacency list representation
    void print() {
        cout << "\nAdjacency List:" << endl;
        for (auto& pair : adjacencyList) {
            cout << pair.first << " -> ";
            for (T neighbor : pair.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // Count vertices
    int vertexCount() {
        return adjacencyList.size();
    }

    // Count edges (works for undirected graphs)
    int edgeCount() {
        int count = 0;
        for (auto& pair : adjacencyList) {
            count += pair.second.size();
        }
        return count / 2;  // Divide by 2 because each edge is counted twice
    }
};

// ============================================================================
// WEIGHTED GRAPH using Adjacency List
// ============================================================================

class WeightedEdge {
public:
    int destination;
    int weight;
    
    WeightedEdge(int dest, int w) : destination(dest), weight(w) {}
};

class WeightedGraph {
private:
    unordered_map<int, list<WeightedEdge>> adjacencyList;

public:
    void addVertex(int vertex) {
        if (adjacencyList.find(vertex) == adjacencyList.end()) {
            adjacencyList[vertex] = list<WeightedEdge>();
        }
    }

    void addEdge(int u, int v, int weight) {
        addVertex(u);
        addVertex(v);
        
        // Add edge from u to v
        adjacencyList[u].push_back(WeightedEdge(v, weight));
    }

    void print() {
        cout << "\nWeighted Adjacency List:" << endl;
        for (auto& pair : adjacencyList) {
            cout << pair.first << " -> ";
            for (WeightedEdge edge : pair.second) {
                cout << "(" << edge.destination << ", wt:" << edge.weight << ") ";
            }
            cout << endl;
        }
    }
};

// ============================================================================
// DEMONSTRATION
// ============================================================================
int main() {
    cout << "=== UNDIRECTED GRAPH ADT ===" << endl;
    
    Graph<char> graph;
    
    // Add edges (which also adds vertices)
    cout << "\nAdding edges..." << endl;
    graph.addEdge('A', 'B');
    graph.addEdge('A', 'C');
    graph.addEdge('B', 'D');
    graph.addEdge('C', 'D');
    graph.addEdge('C', 'E');
    graph.addEdge('D', 'E');
    
    graph.print();
    
    // Graph statistics
    cout << "Number of vertices: " << graph.vertexCount() << endl;
    cout << "Number of edges: " << graph.edgeCount() << endl;
    
    // Traversals
    cout << "\nTraversals starting from vertex A:" << endl;
    graph.dfs('A');
    graph.bfs('A');
    
    // Check edges
    cout << "\nEdge checks:" << endl;
    cout << "Edge A-B exists: " << (graph.hasEdge('A', 'B') ? "YES" : "NO") << endl;
    cout << "Edge A-E exists: " << (graph.hasEdge('A', 'E') ? "YES" : "NO") << endl;
    
    // Get adjacent vertices
    cout << "\nAdjacent vertices to C: ";
    for (char neighbor : graph.getAdjacent('C')) {
        cout << neighbor << " ";
    }
    cout << endl;
    
    // ========== DIRECTED GRAPH EXAMPLE ==========
    cout << "\n\n=== DIRECTED GRAPH ADT ===" << endl;
    
    Graph<int> digraph;
    
    cout << "\nAdding directed edges..." << endl;
    digraph.addDirectedEdge(1, 2);
    digraph.addDirectedEdge(1, 3);
    digraph.addDirectedEdge(2, 4);
    digraph.addDirectedEdge(3, 4);
    digraph.addDirectedEdge(4, 5);
    
    digraph.print();
    
    cout << "\nTraversals from vertex 1:" << endl;
    digraph.dfs(1);
    digraph.bfs(1);
    
    // ========== WEIGHTED GRAPH EXAMPLE ==========
    cout << "\n\n=== WEIGHTED GRAPH ADT ===" << endl;
    
    WeightedGraph wgraph;
    
    cout << "\nAdding weighted edges..." << endl;
    wgraph.addEdge(1, 2, 4);
    wgraph.addEdge(1, 3, 2);
    wgraph.addEdge(2, 3, 1);
    wgraph.addEdge(2, 4, 5);
    wgraph.addEdge(3, 4, 8);
    
    wgraph.print();
    
    return 0;
}
