// parallel dfs and bfs using openmp

#include <bits/stdc++.h>
#include <omp.h>
#include <chrono>
using namespace std;


class Graph{
    private:
    int vertices;
    vector<vector<int>> adj;

    public:
    Graph(int v){
        this->vertices = v;
        adj.resize(v);
    }


    void addEdge(int src, int dest){
        adj[src].push_back(dest);
        adj[dest].push_back(src);
    }



    void dfs(int root){
        vector<bool> visited (this->vertices, false);
        stack<int> st;
        st.push(root);

        while(!st.empty()){
            int curNode = st.top();
            st.pop();

            if(!visited[curNode]){
                visited[curNode] = true;
                cout << curNode << " ";

                for(auto neighbor : adj[curNode]){
                    if(!visited[neighbor]){
                        st.push(neighbor);
                    }
                }
            }
        }
        cout << "\n";
    }



    void bfs(int root) {
        vector<bool> visited (this->vertices, false);
        queue<int> queue;
        queue.push(root);

        while(!queue.empty()){
            int curNode = queue.front();
            queue.pop();

            if(!visited[curNode]){
                visited[curNode] = true;
                cout << curNode << " ";

                for(auto neighbor : adj[curNode]){
                    if(!visited[neighbor]){
                        queue.push(neighbor);
                    }
                }
            }
        }
        cout << "\n";
    }



    void dfs_parallel(int root){
        vector<bool> visited (this->vertices, false);
        stack<int> st;
        st.push(root);

        while(!st.empty()){
            int curNode = st.top();
            st.pop();

            if(!visited[curNode]){
                visited[curNode] = true;
                cout << curNode << " ";

                #pragma omp parallel for
                for(auto neighbor : adj[curNode]){
                    if(!visited[neighbor]){
                        st.push(neighbor);
                    }
                }
            }
        }
        cout << "\n";
    }



    void bfs_parallel(int root) {
        vector<bool> visited (this->vertices, false);
        queue<int> queue;
        queue.push(root);

        while(!queue.empty()){
            int curNode = queue.front();
            queue.pop();

            if(!visited[curNode]){
                visited[curNode] = true;
                cout << curNode << " ";

                #pragma omp parallel for
                for(auto neighbor : adj[curNode]){
                    if(!visited[neighbor]){
                        queue.push(neighbor);
                    }
                }
            }
        }
        cout << "\n";
    }
};



int main() {
    // int v;
    // cout << "Enter no of vertices: ";
    // cin >> v;

    // Graph g(v);

    // int edgeCount;
    // cout << "Enter no of edges: ";
    // cin >> edgeCount;
    
    // cout << "Enter edges: \n";
    // for(int i=0; i<edgeCount; i++){
    //     int ver1, ver2;
    //     cin >> ver1 >> ver2;
    //     g.addEdge(ver1, ver2);
    // }


    int v = 6;
    Graph g(v);
    g.addEdge(0, 1);
    g.addEdge(0, 3);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);


    int src;
    cout << "Enter starting vertex for DFS and BFS (out of 0 to " << v-1 << ") : ";
    cin>> src;

    cout << "DFS starting from vertex " << src << "\n";
    
    
    cout << "Sequential DFS: ";
    auto start = chrono::high_resolution_clock().now();
    g.dfs(src);
    auto stop = chrono::high_resolution_clock().now();
    cout << "Time take by sequential DFS = " << chrono::duration_cast<chrono::microseconds>(stop - start).count() << " ms\n";
    

    cout << "Parallel DFS: ";
    start = chrono::high_resolution_clock().now();
    g.dfs_parallel(src);
    stop = chrono::high_resolution_clock().now();
    cout << "Time take by parallel DFS = " << chrono::duration_cast<chrono::microseconds>(stop - start).count() << " ms\n";


    cout << "\nBFS starting from vertex " << src << "\n";
    cout << "Sequential BFS: ";
    start = chrono::high_resolution_clock().now();
    g.bfs(src);
    stop = chrono::high_resolution_clock().now();
    cout << "Time take by sequential BFS = " << chrono::duration_cast<chrono::microseconds>(stop - start).count() << " ms\n";


    cout << "Parallel DFS: ";
    start = chrono::high_resolution_clock().now();
    g.bfs_parallel(src);
    stop = chrono::high_resolution_clock().now();
    cout << "Time take by parallel BFS = " << chrono::duration_cast<chrono::microseconds>(stop - start).count() << " ms\n";

    cout << "\n";

    return 0;
}


// g++ -fopenmp code.cpp -o output
// ./output 


// Enter starting vertex for DFS and BFS (out of 0 to 5) : 4
// DFS starting from vertex 4
// Sequential DFS: 4 5 3 2 1 0 
// Time take by sequential DFS = 32 ms
// Parallel DFS: 4 5 
// Time take by parallel DFS = 1615 ms

// BFS starting from vertex 4
// Sequential BFS: 4 3 5 0 2 1 
// Time take by sequential BFS = 42 ms
// Parallel DFS: 4 5 3 0 2 1 
// Time take by parallel BFS = 80 ms
