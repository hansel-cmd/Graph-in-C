#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/** 
	1. Given an edgeList, create the Adjacency Matrix to be returned to the
		calling function, and
	2. Display the Matrix

**/

#define MAX_VERTEX 5
#define MAX 10 // n(n - 1)/2 yields 10

/* An unweighted, undirected Edge */
typedef struct {
	int vertex;
	int adj_vertex;
}edgeType;

typedef struct {
	edgeType Edge[MAX];
	int edge_count;
}EdgeList;

typedef int MATRIX_1[MAX_VERTEX][MAX_VERTEX]; // static
typedef int ** MATRIX; // dynamic


// MATRIX func_name
int ** createAdjacencyMatrix(EdgeList E)
{
    int ** MATRIX;
    // each element has to be an array.
    MATRIX = (int **) calloc (MAX_VERTEX, sizeof(int *));

    // initialize each array element
    for (int i = 0; i < MAX_VERTEX; i++) {
        MATRIX[i] = (int *) calloc (MAX_VERTEX, sizeof(int));
    }

    for (int i = 0; i < E.edge_count; i++) {
        
        // get vertex and adjacency vertex
        int u = E.Edge[i].vertex;
        int v = E.Edge[i].adj_vertex;

        // insert to [u][v] only
        MATRIX[u][v] = 1;

    }
    return MATRIX;
}
                    // int ** M
void displayMatrix(MATRIX M)
{
    printf("%3c", ' ');
    for (int i = 0; i < MAX_VERTEX; i++)
        printf("%d ", i);

    for (int i = 0; i < MAX_VERTEX; i++) {
        printf("\n%d: ", i);
        for (int j = 0; j < MAX_VERTEX; j++)
            printf("%d ", M[i][j]);
    }
}

int main()
{
	EdgeList E = {
					{{0,1},{0,2},{0,3},{0,4},
						{1,2},{2,3},{2,4},{3,4}}, 
					8
					};
	int ** M; // or MATRIX M;
	
	M = createAdjacencyMatrix(E);
	displayMatrix(M);
					
	/** 
				Expected Output
				{0, 1, 1, 1, 1},
				{0, 0, 1, 0, 0},
				{0, 0, 0, 1, 1},
				{0, 0, 0, 0, 1},
				{0, 0, 0, 0, 0},
	**/
	return 0;
}