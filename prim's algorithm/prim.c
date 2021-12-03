#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct_definition.h"
#include "helper.h"

/**
 *              This is Prim's algorithm. It is used for finding the Minimum Spanning Tree of a graph.
 *                   This version of Prim's algorithm is similar to Dijkstra's native style. This algorithm
 *                  can also be implemented using a minimum priority queue.
 * 
 *              What it returns is the minimum spanning tree, therefore, a list of edges.
 * 
 **/

edgeType *prim(MATRIX M, int source)
{
    // MAX_VERTEX - 1 since a spanning tree contains pair of vertices
    // hence an edge, and the minimum edge a graph (mst) can have is 
    // number of vertices - 1
    edgeType *mst = (edgeType *) malloc (sizeof(edgeType) * (MAX_VERTEX - 1));
    if (!mst) return NULL;

    // visited vertices
    int visited[MAX_VERTEX];
    memset(visited, 0, sizeof(visited));

    // make the source visited
    // and the next vertex
    visited[source] = 1;
    int next_vertex = source;

    for (int count = 0; count < MAX_VERTEX - 1; count++) {
        
        // for every iteration, set min_cost to INFINITY
        // to get the next minimum cost
        int min_cost = INFINITY;

        // get the minimum cost from visited vertices
        // to the unvisited neighboring vertices
        int current_vertex, vertex;
        for (current_vertex = 0; current_vertex < MAX_VERTEX; current_vertex++) {
            if (visited[current_vertex]) {
                // check the unvisited neighbor and get the
                // vertex that has the minimum cost
                for (int neighbor = 0; neighbor < MAX_VERTEX; neighbor++) {
                    // if the neighbor is unvisited and 
                    // the distance from current vertex to this neighbor vertex is the minimum
                    if (!visited[neighbor] && min_cost > M[current_vertex][neighbor]) {
                        min_cost = M[current_vertex][neighbor];
                        // pairs => vertex, next_vertex
                        // this is the edge
                        // with the minimum cost
                        next_vertex = neighbor;
                        vertex = current_vertex;
                    }
                }
            }
        }

        // mark the next_vertex as visited
        visited[next_vertex] = 1;
        // we add the edge (vertex, next_vertex) to the mst
        mst[count].vertex = vertex;
        mst[count].adj_vertex = next_vertex;
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

    int source = 0;
    edgeType *minimum_cost = prim(M, source);
    displayPrim(minimum_cost);

    return 0;
}