#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct_definition.h"
#include "helper.h"

/**
 *      Warshall's algorithm is similar to Floyd's algorithm. However, this algorithm is used
 *          to determine the transitive closure of the graph. What it means is that it 
 *          determines whether or not there is a path from this vertex to other vertices.
 *      If there is a path, we make it 1, otherwise 0.
 * 
 * 
 *      This algorithm is really good in a matrix representation of a graph. So, your task is
 *      to do Warshall's algorithm in an adjacency list.
 *      Hint: It is easier if u convert the list representation to matrix representation. xD
 * 
 **/

int **warshall(MATRIX M)
{
    // The algorithm should only be used in a directed graph.
    // If it were an undirected graph, chances are, there is a path
    // from 1 vertex to another.
    // This algorithm can be used in a weighted graph. 
    // If there is a weight, it means there is a path.

    // initialize a matrix to be returned
    int **matrix = (int **) calloc (MAX_VERTEX, sizeof(int *));
    for (int i = 0; i < MAX_VERTEX; i++)
        matrix[i] = (int *) calloc (MAX_VERTEX, sizeof(int));

    // copy all the elements from the original matrix
    // to the matrix that is to be returned
    for (int i = 0; i < MAX_VERTEX; i++) {
        for (int j = 0; j < MAX_VERTEX; j++)
            matrix[i][j] = M[i][j];
    }

    // We need to loop all the vertices. This is the outer loop.
    // The 2 inner loops are used to traverse the matrix.
    for (int k = 0; k < MAX_VERTEX; k++) {
        for (int i = 0; i < MAX_VERTEX; i++) {
            for (int j = 0; j < MAX_VERTEX; j++) {
                    matrix[i][j] = matrix[i][j] || matrix[i][k] && matrix[k][j];
            }
        }
    }

    /**
     *
     *          The visualization is similar to Floyd's. See floyd's algorithm inside 
     *              floyd's algorithm folder.
     * 
     **/

    return matrix;
}

void displayWarshall(int ** M)
{
    printf("\n");
    for (int i = 0; i < MAX_VERTEX; i++) {
        for (int j = 0; j < MAX_VERTEX; j++)
            printf("%4d ", M[i][j]);
        printf("\n");
    }
}

int main()
{
    MATRIX M = {
        {0, 1, 1, 0, 0},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {1, 0, 0, 0, 0}
    };

    displayMatrix(M);

    int **transitive_closure = warshall(M);
    displayWarshall(transitive_closure);

    return 0;
}
