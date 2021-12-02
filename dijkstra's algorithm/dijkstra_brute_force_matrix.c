#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "struct_definition.h"
#include "helper.h"


/**
 *
 *      This is the native dijkstra's algortihm with O(n^2) time complexity.
 *          Although it is slower compared to the version where I use min heap,
 *          this algorithm is easy to follow and visualize. It is also
 *              easy to implement esp if the language used is python or javascript
 * 
 * 
 **/


int *dijkstra(MATRIX M, int source)
{
    // create a distance variable containing the shortest distance
    // from the source to the index (vertex)
    int *distance = (int *) malloc(MAX_VERTEX * sizeof(int));
    if (!distance)
        return NULL;

    // OPTIONAL - BUT USUALLY RETURNED TOGETHER WITH THE SHORTEST DISTANCE
    // create a path variable containing the shortest path from
    // the source to the index (vertex)
    int *path = (int *) malloc (MAX_VERTEX * sizeof(int));
    if (!path)
        return NULL;
    for (int i = 0; i < MAX_VERTEX; i++) path[i] = source;
    // for some reason, memset won't work sa vscode but works fine sa uban
    // memset(path, source, sizeof(int) * MAX_VERTEX);

    // Create a list of vertices
    int vertices[MAX_VERTEX];
    for (int i = 0; i < MAX_VERTEX; i++) vertices[i] = i;

    // Create a list of visited vertices.
    // In C, it is better to use bit-vector if u want
    // to optimize running time - but this will cost
    // u space. In other languages, it is better to use
    // a Set data structure esp in python and js.
    // Initialize to false.
    int visited[MAX_VERTEX];
    memset(visited, 0, sizeof(visited));

    // initialize the current distance from source to other vertices
    for (int i = 0; i < MAX_VERTEX; i++) distance[i] = M[source][i];

    // mark the source vertex as visited and initialize the distance
    // of the source vertex to itself as 0.
    visited[source] = 1;
    distance[source] = 0;

    // We set source as our next vertex
    int next_vertex = source;
    // path[next_vertex] = -1; <- this is optional.

    // we start from 1 because there are n - 1 vertices left to explore.
    for (int i = 1; i < MAX_VERTEX; i++) {

        // For every iteration, we need to have the minimum distance
        // set to infinity so as to get the next shortest distance.
        int minimum_distance = INFINITY;

        // get the next vertex which follows the ff rules:
        // the vertex is not yet visited
        // and has the smallest distance
        for (int vertex = 0; vertex < MAX_VERTEX; vertex++) {
            if (!visited[vertex] && distance[vertex] < minimum_distance) {
                minimum_distance = distance[vertex];
                next_vertex = vertex;
            }
        }

        // mark the next_vertex as visited
        visited[next_vertex] = 1;

        // update the next_vertex's unvisited neighbor's distance
        // what happens? 
        // if the known distance of this neighbor is greater than
        // the new path created by this next_vertex, then we update
        // the distance of this neighbor.
        // $$ distance[neighbor] > distance[next_vertex] + M[next_vertex][neighbor]
        // known distance of neighbor  > distance(vertex) + distance(vertex -> neighbor)
        for (int neighbor = 0; neighbor < MAX_VERTEX; neighbor++) {
            // we can make this as 1 if statement with multi condition
            // but it will be harder to read. Also, It won't make your code faster.
            if (!visited[neighbor]) {
                if (distance[neighbor] > distance[next_vertex] + M[next_vertex][neighbor]) {
                    distance[neighbor] = distance[next_vertex] + M[next_vertex][neighbor];
                    // path[neighbor] = next_vertex; <- this is optional.
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


