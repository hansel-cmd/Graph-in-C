#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct_definition.h"
#include "helper.h"

/**
 *              This is Prim's algorithm. It is used for finding the Minimum Spanning Tree of a graph.
 *              This algo implementation uses minimum priority queue.
 * 
 *              This algorithm runs at O(E log V). It is significantly faster than the previous
 *              implementation, but is longer to write.
 *              
 *              What it returns is the minimum spanning tree, therefore, a list of edges.
 * 
 *              Note: Time Complexity calculation is based on an adjacency list                 
 *              representation,
 *              where we only loop the edges and not the vertices. 
 *              (When we loop the neighboring vertices in a list, we are technically looping
 *                the number of edges this vertex has. In a matrix, we are really looping
 *                  all vertices.)
 * 
 **/

typedef struct {
    int vertex;
    int adj_vertex;
    int weight;
} Node;


typedef struct {
    Node node[MAX]; // MAX since there are MAX (10) edges in a MAX_VERTEX (5)
    int last_index;
} PQ;

void insert(PQ *Q, int vertex, int adj_vertex, int weight)
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
        Q->node[current].adj_vertex = adj_vertex;
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

// O (V(log V + E log V))
// O (V log V + VE log V)
// O (VE log V) => VE is just going over all edges for each vertex, so V * E is just E
// O (E log V)
edgeType *prim(MATRIX M, int source)
{
    // MAX - 1 edges
    edgeType *mst = (edgeType *) malloc (sizeof(edgeType) * (MAX_VERTEX - 1));
    int edge_count = 0;
    if (!mst) return NULL;

    // for visited nodes
    int visited[MAX_VERTEX];
    memset(visited, 0, sizeof(visited));

    // initialize priority queue
    PQ queue = {.last_index = -1};

    // Insert all edges from the source vertex
    // we need to insert all because we need to get the minimum edge
    for (int adj_vertex = 0; adj_vertex < MAX_VERTEX; adj_vertex++) {
        // we only insert if there is a path, and
        // the path is not from the vertex to itself
        if (M[source][adj_vertex] != INFINITY && source != adj_vertex)
            insert(&queue, source, adj_vertex, M[source][adj_vertex]);
    }


    // Continue until there are no vertices left to be visited
    // OR until we have MAX_VERTEX - 1 edge count
    // O (log V)
    while (queue.last_index > -1 && edge_count < MAX_VERTEX - 1) {

        // get the next edge
        Node edge = deleteMin(&queue); // O (log V)
        int vertex = edge.vertex; // first vertex of the pair
        int adj_vertex = edge.adj_vertex; // second vertex of the pair

        // if this edge has already been passed through, we skip
        if (visited[vertex] && visited[adj_vertex]) continue;

        // otherwise, we mark the vertices of this edge as visited
        visited[vertex] = visited[adj_vertex] = 1;

        // add this to the mst => since this edge contains the minimum cost
        mst[edge_count].vertex = vertex;
        mst[edge_count++].adj_vertex = adj_vertex;

        // Get all the next edges from the current adj_vertex
        // O (E)
        for (int current_vertex = 0; current_vertex < MAX_VERTEX; current_vertex++) {
            // if the current vertex (a.k.a - next_vertex of the current adj_vertex)
            // is not yet visited, and an edge is present from adj_vertex to this current_vertex
            // O (log V)
            if (!visited[current_vertex] && M[adj_vertex][current_vertex] != INFINITY)
                insert(&queue, adj_vertex, current_vertex, M[adj_vertex][current_vertex]);
        }
    }

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
    printf("\n");
    int source = 0;
    edgeType *minimum_cost = prim(M, source);
    displayPrim(minimum_cost);

    return 0;
}