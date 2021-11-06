/*
Example input:
8 5
0 1 2
0 2 3
1 4 4
2 3 3
3 2 1
3 1 4
4 5 3
4 1 0
------
entry_count,
vertice_count (vmax+1),
from - weight - to
*/

#include <iostream>
#include <iomanip>
#include <fstream>

struct edge
{
    int src;
    int dest;
    int weight;
};

edge* readGraph(char* filename, int &size, int& vertCount) {
    std::fstream file(filename);
    file >> size >> vertCount;
    edge* graph = new edge[size];
    for (int i = 0; i < size; i++) {
        int src;
        int dest;
        int weight;
        file >> src >> weight >> dest;
        graph[i] = edge{ src, dest, weight };
    }

    return graph;
}

edge* makeUnoriented(edge* graph, int &size) {
    edge* unoriented = new edge[2*size];
    std::copy(graph, graph + size, unoriented);

    int oldSize = size;

    for (int i = 0; i < oldSize; i++)
    {
        bool found = false;
        for (int j = i; j < oldSize; j++)
        {
            if (unoriented[i].src == unoriented[j].dest && unoriented[i].dest == unoriented[j].src) {
                found = true;
                break;
            }
        }
        if (!found) {
            unoriented[size] = edge{ unoriented[i].dest, unoriented[i].src, unoriented[i].weight };
            size++;
        }
    }
    return unoriented;
}

void printGraph(edge* graph, int size) {
    for (int i = 0; i < size; i++)
    {
        std::cout << graph[i].src << "-(" << graph[i].weight << ")->" << graph[i].dest << std::endl;
    }
}

void bellman_ford(edge* graph, int sourceVertex, int edgeCount, int verticeCount)
{
    std::cout << "\nSource:" << sourceVertex << std::endl;
    int from, to, weight = 0;
    int* distances = new int[verticeCount];

    /* initializing array 'dis' with 999. 999 denotes infinite distance */
    for (int i = 0; i < verticeCount; i++)
    {
        distances[i] = INT_MAX;
    }

    /* distance of source vertex from source vertex is o */
    distances[sourceVertex] = 0;

    /* relaxing all the edges verticeCount - 1 times */
    for (int i = 0; i < verticeCount - 1; i++)
    {
        for (int j = 0; j < edgeCount - 1; j++)
        {
            from = graph[j].src;
            to = graph[j].dest;
            weight = graph[j].weight;

            if (distances[from] != INT_MAX && distances[from] + weight < distances[to])
            {
                distances[to] = distances[from] + weight;
            }

            std::cout << "\nVertex" << "\tDistance";
            for (int i = 0; i < verticeCount; i++)
            {
                if (distances[i] == INT_MAX) {
                    std::cout << "\n" << i << "\t" << "INF";
                }
                else {
                    std::cout << "\n" << i << "\t" << distances[i];
                }

            }
        }
    }


}



//Helper. Returns -1 if edge doesnt exist
int edgeWeight(int from, int to, edge* graph, int gSize) {
    for (int i = 0; i < gSize; i++) {
        if (graph[i].src == from && graph[i].dest == to) {
            return graph[i].weight;
        }
    }

    return -1;
}

// Function to find the vertex with minimum key value 
int min_Key(int key[], bool visited[], int verticeCount)
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < verticeCount; v++) {
        if (visited[v] == false && key[v] < min) {
            // vertex should not be visited
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void printMST(int* edges, int vCount, edge* graph, int gSize) {
    std::cout << "MST Edges:\n";
    for (int i = 0; i < vCount; i++) {
        if (edges[i] != -1) std::cout << i << "-(" << edgeWeight(i, edges[i], graph, gSize) << ")->" << edges[i] << std::endl;
    }

}

void Prims_MST(edge* graph, int graphSize, int verticeCount)
{  
    int* edges = new int[verticeCount];
    int* key = new int[verticeCount];
    bool* visited = new bool[verticeCount];

    // Initialize all the arrays 
    for (int i = 0; i< verticeCount; i++) {
        key[i] = INT_MAX;
        visited[i] = false;
        edges[i] = -1;
    }    

    key[0] = 0;  // Include first vertex in MST by setting its key vaue to 0.  
    edges[0] = -1; // First node is always root of MST  

    // The MST will have maximum V-1 vertices  
    for (int x = 0; x < verticeCount - 1; x++)
    {  
        // Finding the minimum key vertex from the 
        //set of vertices not yet included in MST  
        int u = min_Key(key, visited, verticeCount);

        visited[u] = true;  // Add the minimum key vertex to the MST  

        // Update key and parent arrays
        for (int v = 0; v < verticeCount; v++)
        {
            // cost[u][v] is non zero only for adjacent vertices of u  
            // visited[v] is false for vertices not yet included in MST  
            // key[] gets updated only if cost[u][v] is smaller than key[v]  
            if (edgeWeight(u,v,graph,graphSize) >= 0 && visited[v] == false && edgeWeight(u, v, graph, graphSize) < key[v])
            {  
                edges[v] = u;
                key[v] = edgeWeight(u, v, graph, graphSize);
            }        
        }
        printMST(edges, verticeCount, graph, graphSize);
    }

}  


int main()
{
    char* fname = new char[1024];
    int size, vertcount;
    std::cout << "Input filename: ";
    std::cin >> fname;
    edge* graph = readGraph(fname, size, vertcount);
    std::cout << "Graph:" << std::endl;
    printGraph(graph, size);
    bellman_ford(graph, 0, size, vertcount);
    std::cout << '\n';
    std::cout << std::endl;

    edge* ugraph = makeUnoriented(graph, size);
    Prims_MST(ugraph, size, vertcount);

    return 0;
}