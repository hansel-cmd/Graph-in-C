#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "struct_definition.h"
#include "helper.h"

typedef struct {
    int vertex;
    int weight;
} Node;

typedef struct {
    Node node[MAX_VERTEX];
    int last_index;
} PQ;

void insert(PQ *Q, int vertex, int weight)
{
    if (Q->last_index < MAX_VERTEX - 1) {

        int current, parent;
        current = ++Q->last_index;
        
        parent = (current - 1) / 2;
        while (current > 0 && Q->node[parent].weight > weight) {
            Q->node[current] = Q->node[parent];
            current = parent;
            parent = (parent - 1) / 2;
        }
        Q->node[current].vertex = vertex;
        Q->node[current].weight = weight;
    }
}

Node deleteMin(PQ *Q)
{
    Node node;
    if (Q->last_index >= 0) {
        int current = 0, child = 1;

        node = Q->node[current];
        Q->node[current] = Q->node[Q->last_index--];

        Node temp;
        while (child <= Q->last_index) {
            if (child + 1 <= Q->last_index && Q->node[child].weight > Q->node[child + 1].weight) {
                child++;
            }

            if (Q->node[current].weight > Q->node[child].weight) {
                temp = Q->node[current];
                Q->node[current] = Q->node[child];
                Q->node[child] = temp;

                current = child;
                child = 2 * child + 1;
            } else {
                break;
            }
        }
    }
    return node;
}

// O (N + V log N)
int *dijkstra(MATRIX M, int source)
{
    
    PQ Q = {.last_index = -1};
    int *distance = (int *) malloc (MAX_VERTEX * sizeof(int));
    if (!distance) return NULL;
    for (int i = 0; i < MAX_VERTEX; i++) distance[i] = INFINITY;

    distance[source] = 0;
    insert(&Q, source, 0);

    Node temp;
    // O (N) where N is the number of vertices
    while (Q.last_index > -1) {
        temp = deleteMin(&Q); // O (log n)
        int current_vertex = temp.vertex;

        // O (V) where n is the number of neighboring vertices
        for (int neighbor = 0; neighbor < MAX_VERTEX; neighbor++) {
            if (M[current_vertex][neighbor] != INFINITY && M[current_vertex][neighbor] != 0) {

                if (distance[neighbor] > distance[current_vertex] + M[current_vertex][neighbor]) {
                    distance[neighbor] = distance[current_vertex] + M[current_vertex][neighbor];
                    insert(&Q, neighbor, distance[neighbor]); // O (log n)
                }
            }
        }
    }

    return distance;
    
}

void displayShortestDistance(int distance[], int source)
{
    printf("\n\nSource vertex: %d", source);
    for (int i = 0; i < MAX_VERTEX; i++)
        printf("\nShortest distance from %d to %d: %d", source, i, distance[i]);
}

void main()
{
    MATRIX M = {
        {9999, 30, 25, 9999, 50},
        {30, 9999, 9999, 90, 30},
        {25, 9999, 9999, 40, 9999},
        {9999, 90, 40, 9999, 10},
        {50, 30, 9999, 10, 9999}
    };

    displayMatrix(M);

    /**
     *  graph is undirected
     *  where (x) is the node
     *  and --y-- is the weight
     * 
     * 
     * 
     *                  (2) -------25-------(0)
     *                   |                   | \   
     *                   |                   |  \ 
     *                   |                  30   \ 
     *                   |                   |    \
     *                   |                   |     50
     *                   40         |------ (1)     \   
     *                   |          |         \      \
     *                   |          |          \      |
     *                   |  ---90----          30     | 
     *                   | /                     \    | 
     *                  (3) ---------10----------(4)--|
     **/


    int source = 0;
    int *shortest_distance = dijkstra(M, source);
    displayShortestDistance(shortest_distance, source);

}