/*
Example input:
13 10
0 -1 1
1 1 2
2 2 3
3 4 4
4 9 5
5 1 6
6 3 7
7 5 8
8 2 0
0 6 9
9 1 7
9 5 3
2 0 6
8 -4 4
------
entry_count,
vertice_count (vmax+1),
from - weight - to
*/

#include <iostream>
#include <iomanip>
#include <fstream>

struct edge {
    int src;
    int dest;
    int weight;
};

//Считывает граф из файла и определяет количество граней и вершин
edge* readGraph(char* filename, int& size, int& vertCount) {
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

// Делает граф неориентированным. Веса усредняются
edge* makeUnoriented(edge* graph, int& size) {
    edge* unoriented = new edge[2 * size];
    std::copy(graph, graph + size, unoriented);

    int oldSize = size;

    for (int i = 0; i < oldSize; i++) {
        bool found = false;
        for (int j = i; j < oldSize; j++) {
            if (unoriented[i].src == unoriented[j].dest && unoriented[i].dest == unoriented[j].src) {
                unoriented[i].weight = unoriented[j].weight = (unoriented[i].weight + unoriented[j].weight) / 2;
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

// Выводит граф в консоль
void printGraph(edge* graph, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << graph[i].src << "-(" << graph[i].weight << ")->" << graph[i].dest << std::endl;
    }
}

// Вывод резульата работы bellmanFord
void printBF(int* pred, int size) {
    std::cout << "\n\nShortest path: " << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << pred[i] << '-' << i << std::endl;
    }
}

// Обрабатывает граф алгоритмом Беллмана-Форда
int* bellmanFord(edge* graph, int sourceVertex, int edgeCount, int verticeCount) {
    std::cout << "\nSource vertice:" << sourceVertex << std::endl;
    int from, to, weight = 0;
    int* shortest = new int[verticeCount];
    int* pred = new int[verticeCount];

    // Для всех вершин устанавливаем inf
    for (int i = 0; i < verticeCount; i++) {
        shortest[i] = INT_MAX;
        pred[i] = -1;
    }

    // Расстояние от корня до него же 0
    shortest[sourceVertex] = 0;

    // Релаксация verticeCount - 1 раз
    for (int i = 0; i < verticeCount - 1; i++) {
        // Для каждого ребра
        for (int j = 0; j < edgeCount; j++) {
            from = graph[j].src;
            to = graph[j].dest;
            weight = graph[j].weight;

            //Производим релаксацию
            if (shortest[from] != INT_MAX && shortest[from] + weight < shortest[to]) {
                shortest[to] = shortest[from] + weight;
                pred[to] = from;
            }
        }

        //Выводим верлшины
        std::cout << "\nVert" << "\tDist" << "\tPred";
        for (int i = 0; i < verticeCount; i++) {
            std::cout << "\n" << i << "\t";
            if (shortest[i] == INT_MAX) {
                std::cout << "INF";
            }
            else {
                std::cout << shortest[i];
            }
            std::cout << '\t' << pred[i];
        }
    }
    printBF(pred, verticeCount);
    return pred;
}

//Получает вес ребра from-to. Возвращает INT_MAX если ребра нет
int edgeWeight(int from, int to, edge* graph, int gSize) {
    for (int i = 0; i < gSize; i++) {
        if (graph[i].src == from && graph[i].dest == to) {
            return graph[i].weight;
        }
    }
    return INT_MAX;
}

// Обрабатывает граф алгоритмом прима. Печатает полученное дерево.
void primMST(edge* graph, int graphSize, int verticeCount, int& treeSize) {
    bool* chosenVertices = new bool[verticeCount];
    edge* chosenEdges = new edge[graphSize];
    treeSize = 0;
    memset(chosenVertices, false, verticeCount);
    chosenVertices[0] = true; // Добавляем вершину 0 как корень

    for (int i = 0; i < verticeCount - 1; i++) {
        // Определить веса между всеми выбранными вершинами и  остальными невыбранными вершинами
        // И выбрать наименьший вес
        int min = INT_MAX;
        int minVertice;
        int from;
        for (int j = 0; j < verticeCount; j++) {

            //Если вершина в дереве
            if (chosenVertices[j]) {
                //Перебираем все возможные связи
                for (int k = 0; k < verticeCount; k++) {
                    if (!chosenVertices[k] && edgeWeight(j, k, graph, graphSize) != INT_MAX && edgeWeight(j, k, graph, graphSize) < min) {
                        from = j;
                        min = edgeWeight(j, k, graph, graphSize);
                        minVertice = k;
                    }
                }
            }
        }
        if (min != INT_MAX) {
            // Добавить вершину к выбранным
            chosenVertices[minVertice] = true;
            chosenEdges[treeSize] = edge{ from, minVertice, min };
            treeSize++;
            printGraph(chosenEdges, treeSize);
            std::cout << std::endl;
        }
    }
}

int main() {
    char* fname = new char[1024];
    int size, vertcount;
    std::cout << "Input filename: ";
    std::cin >> fname;
    edge* graph = readGraph(fname, size, vertcount);
    std::cout << "Read graph:" << std::endl;
    printGraph(graph, size);
    bellmanFord(graph, 0, size, vertcount);
    std::cout << '\n';
    std::cout << std::endl;

    std::cout << "Minimum spanning tree:" << std::endl;
    edge* ugraph = makeUnoriented(graph, size);
    int usize;
    primMST(ugraph, size, vertcount, usize);

    return 0;
}
