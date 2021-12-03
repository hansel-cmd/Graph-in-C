#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct_definition.h"
#include "helper.h"

/**
 *              This is Prim's algorithm. It is used for finding the Minimum Spanning Tree of a graph.
 *              This algo implementation uses minimum priority queue.
 *              
 *              What it returns is the minimum spanning tree, therefore, a list of edges.
 * 
 **/

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

edgeType *prim(MATRIX M, int source)
{
    // MAX - 1 edges
    edgeType *mst = (edgeType *) malloc (sizeof(edgeType) * (MAX_VERTEX - 1));
    if (!mst) return NULL;

    // for visited nodes
    int visited[MAX_VERTEX];
    memset(visited, 0, sizeof(visited));

    // initialize priority queue
    PQ queue = {.last_index = -1};

    // insert the source vertex to the queue
    // and mark it as visited
    insert(&queue, source, 0);
    visited[source] = 1;

    





    return mst;
}

void displayPrim(edgeType mst[])
{
    printf("\nMST Edges");
    for (int i = 0; i < MAX_VERTEX - 1; i++)
        printf("\n(%d, %d)", mst[i].vertex, mst[i].adj_vertex);
}

int main()
{
    MATRIX M = {
        {INFINITY, 30, 25, INFINITY, 50},
        {30, INFINITY, INFINITY, 90, 30},
        {25, INFINITY, INFINITY, 40, INFINITY},
        {INFINITY, 90, 40, INFINITY, 10},
        {50, 30, INFINITY, 10, INFINITY}
    };
    displayMatrix(M);

    int source = 0;
    edgeType *minimum_cost = prim(M, source);
    displayPrim(minimum_cost);

    return 0;
}