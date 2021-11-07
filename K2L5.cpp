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

void bellmanFord(edge* graph, int sourceVertex, int edgeCount, int verticeCount)
{
    std::cout << "\nSource:" << sourceVertex << std::endl;
    int from, to, weight = 0;
    int* shortest = new int[verticeCount];

    // Для всех вершин устанавливаем inf
    for (int i = 0; i < verticeCount; i++)
    {
        shortest[i] = INT_MAX;
    }

    /* distance of source vertex from source vertex is o */
    shortest[sourceVertex] = 0;

    /* relaxing all the edges verticeCount - 1 times */
    for (int i = i; i < verticeCount - 1; i++)
    {
        for (int j = 0; j < edgeCount - 1; j++)
        {
            from = graph[j].src;
            to = graph[j].dest;
            weight = graph[j].weight;

            if (shortest[from] != INT_MAX && shortest[from] + weight < shortest[to])
            {
                shortest[to] = shortest[from] + weight;
            }

            std::cout << "\nVertex" << "\tDistance";
            for (int i = 0; i < verticeCount; i++)
            {
                if (shortest[i] == INT_MAX) {
                    std::cout << "\n" << i << "\t" << "INF";
                }
                else {
                    std::cout << "\n" << i << "\t" << shortest[i];
                }

            }
        }
    }


}



//Helper. Returns INT_MAX if edge doesnt exist
int edgeWeight(int from, int to, edge* graph, int gSize) {
    for (int i = 0; i < gSize; i++) {
        if (graph[i].src == from && graph[i].dest == to) {
            return graph[i].weight;
        }
    }
    return INT_MAX;
}

void primMST(edge* graph, int graphSize, int verticeCount, int& treeSize)
{  
    bool* chosenVertices = new bool[verticeCount];
    edge* chosenEdges = new edge[graphSize];
    treeSize = 0;
    memset(chosenVertices, false, verticeCount);
    chosenVertices[0] = true; // Добавляем вершину 0 как корень
    
    for (int i = 0; i < verticeCount - 1; i++) {
        // Определить веса между всеми выбранными вершинами и  остальными невыбранными вершинами
        // И выбрать наименьший вес
        for (int j = 0; j < verticeCount; j++) {
            int min = INT_MAX;
            int minVertice;
            //Если вершина в дереве
            if (chosenVertices[j]) {
                //Перебираем все возможные связи
                for (int k = 0; k < verticeCount; k++)
                {
                    if (!chosenVertices[k] && edgeWeight(j, k, graph, graphSize) != INT_MAX && edgeWeight(j, k, graph, graphSize) < min) {
                        min = edgeWeight(j, k, graph, graphSize);
                        minVertice = k;
                    }
                }

                if (min != INT_MAX) {
                    // Добавить вершину к выбранным
                    chosenVertices[minVertice] = true;
                    chosenEdges[treeSize] = edge{ j, minVertice, min };
                    treeSize++;
                    printGraph(chosenEdges, treeSize);
                    std::cout << std::endl;
                }

            }

        }
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
    bellmanFord(graph, 0, size, vertcount);
    std::cout << '\n';
    std::cout << std::endl;

    edge* ugraph = makeUnoriented(graph, size);
    int usize;
    primMST(ugraph, size, vertcount, usize);

    return 0;
}
