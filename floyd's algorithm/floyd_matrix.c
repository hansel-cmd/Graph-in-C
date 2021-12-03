#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct_definition.h"
#include "helper.h"

/**
 *      Floyd's algorithm is used to get the shortest path of all vertices to the rest
 *          of the vertices. We know that Dijkstra's algorithm is used to get the 
 *          shortest path of 1 source vertex to all other vertices, this means that we could
 *              potentially use Dijkstra's algorithm to get all the shortest path of 
 *              each vertices by looping the algorithm n times, where n is the number 
 *              of vertices in the graph. Each iteration would have a new source vertex 
 *              and then find the shortest path of that vertex.
 *  
 *      However, it is not efficient. By using the concept of dynamic programming, 
 *      (it's just a fancy way of saying 'breaking down the problem into smaller problems to 
 *       reach optimal solution'), we can easily get the shortest path of all vertices.
 *  
 *      This algorithm is really good in a matrix representation of a graph. So, your task is
 *      to do Floyd's algorithm in an adjacency list.
 *      Hint: It is easier if u convert the list representation to matrix representation. xD
 * 
 **/

int **floyd(MATRIX M)
{
    // Note that for this to work, all vertices that do not have
    // a direct relation with each other should have INFINITY as its distance.

    // initialize a matrix to be returned
    int **matrix = (int **) calloc (MAX_VERTEX, sizeof(int *));
    for (int i = 0; i < MAX_VERTEX; i++)
        matrix[i] = (int *) calloc (MAX_VERTEX, sizeof(int));

    // copy all the elements from the original matrix
    // to the matrix that is to be returned
    // U can also use 2 for loops here.
    // memcpy will only work if both matrix have the same data type.
    // if 1 data type is a dynamic matrix, then the other one should also be
    // a dynamic matrix. To be safe, just use 2 for loops.
    // memcpy(&matrix, &M, sizeof(matrix));
    for (int i = 0; i < MAX_VERTEX; i++) {
        for (int j = 0; j < MAX_VERTEX; j++)
            matrix[i][j] = M[i][j];
    }

    // We set the diagonal to 0 because the distance from
    // the source vertex to itself is 0.
    for (int i = 0; i < MAX_VERTEX; i++) matrix[i][i] = 0;

    // We need to loop all the vertices. This is the outer loop.
    // The 2 inner loops are used to traverse the matrix.
    for (int k = 0; k < MAX_VERTEX; k++) {
        for (int i = 0; i < MAX_VERTEX; i++) {
            for (int j = 0; j < MAX_VERTEX; j++) {
                if (matrix[i][j] > matrix[i][k] + matrix[k][j])
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
            }
        }
    }

    /**
     *
     *          One way to visualize what's happening:
     *
     *          ALWAYS remember to not touch the diagonal because again,
     *              the distance of a vertex to itself is 0. 
     * 
     *          I will set the diagonal as "y" <- this is to tell u to not 
     *          touch this cell.
     * 
     *          Consider this matrix:
     *          when k = 0, this means that we do not touch
     *              the column 0 and row 0.
     *  
     *              0   1   2   3   4
     *          0   x   x   x   x   x
     *          1   x   y
     *          2   x       y
     *          3   x           y
     *          4   x               y
     * 
     *          With that, we get the value of all the cells that are "blank". Technically,
     *              it has a value but do not mind that. Let's say we want to get the value
     *              at [1, 2] -> I will mark this "z".
     * 
     *              0   1   2   3   4
     *          0   x   x   x   x   x
     *          1   x   y   z
     *          2   x       y
     *          3   x           y
     *          4   x               y
     * 
     *          What we do is get the x's that makes z its intersection. In this case, the
     *          [1, 0] and [0, 2]. Here, we add the numbers inside these 2 cells and make that  
     *          "A", and compare its value to the value inside the cell where z is located. If the 
     *          value of z is greater than the A, then we update the value of z with A. 
     * 
     *          U do the same to the rest of the cells that are "blank". And then increment k.
     * 
     *          So, when k = 1, then do not touch the column 1 and row 1.
     *
     * 
     **/

    return matrix;
}

void displayFloyd(int ** M)
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
        {INFINITY, 30, 125, INFINITY, 50},
        {30, INFINITY, INFINITY, 90, 30},
        {125, INFINITY, INFINITY, 40, INFINITY},
        {INFINITY, 90, 40, INFINITY, 10},
        {50, 30, INFINITY, 10, INFINITY}
    };

    displayMatrix(M);

    int **apsp_floyd = floyd(M);
    displayFloyd(apsp_floyd);

    return 0;
}
