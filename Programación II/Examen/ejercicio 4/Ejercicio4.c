#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>


#define V 6 // Número de nodos en el grafo

int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;
  
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
  
    return min_index;
}
  
void printPath(int parent[], int j) {
    if (parent[j] == - 1)
        return;
  
    printPath(parent, parent[j]);
  
    printf(" -> %c", j + 'A');
}
  
int printSolution(int dist[], int n, int parent[]) {
    int src = 0;
    printf("Nodo \t\t Distancia \t\t Camino");
    for (int i = 1; i < V; i++) {
        printf("\n%c -> %c \t\t %d \t\t %c", src + 'A', i + 'A', dist[i], src + 'A');
        printPath(parent, i);
    }
}
  
void dijkstra(int graph[V][V], int src) {
    int dist[V]; // Array para guardar las distancias más cortas desde el nodo de origen
    bool sptSet[V]; // Array para mantener un seguimiento de los nodos ya procesados
    int parent[V]; // Array para guardar la ruta más corta
  
    for (int i = 0; i < V; i++) {
        parent[0] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
  
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
  
        sptSet[u] = true;
  
        for (int v = 0; v < V; v++)
  
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
    }
  
    printSolution(dist, V, parent);
}
  
int main() {
    int graph[V][V] = {
        {0, 0, 0, 9, 0, 0},
        {0, 0, 0, 7, 0, 8},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 15, 0},
        {1, 0, 0, 5, 0, 0},
        {0, 0, 6, 0, 4, 0}
    };
  
    dijkstra(graph, 0);
  
    return 0;
}
