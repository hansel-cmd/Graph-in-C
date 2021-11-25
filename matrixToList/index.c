#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// We convert an adj matrix to an adj list
// also, this contains WEIGHTS.
// constraints:
//      for matrix:
//        INF or 999 means no edge/arc
//        weight is what we put in the intersection of (u,v)
//        weight denotes that there is an edge from u to v
//      for list:
//        weight from u to v can be accessed from the node that contains v.


/* Data Structure Definition */

#define MAX_VERTEX 5
#define INF 999

typedef struct node {
	int adj_vertex;
	int weight;
	struct node *next;
}node, *nodePtr;

typedef nodePtr *AdjList; // dynamic adj list
typedef int MATRIX[MAX_VERTEX][MAX_VERTEX]; // static matrix

void displayMatrix(MATRIX M)
{
	for (int i = 0; i < MAX_VERTEX; i++) {
		printf("\n%d: ", i);
		for (int j = 0; j < MAX_VERTEX; j++) {
			M[i][j] == INF ? printf("%3c ", 236) : printf("%3d ", M[i][j]);
		}
		printf("\n");
	}
}

AdjList convertMatrixToList(MATRIX M)
{
    AdjList adj_list;
    adj_list = (AdjList) calloc (MAX_VERTEX, sizeof(node));
    return adj_list;
}

int main()
{
    MATRIX M =	{
                {INF,  10, INF,  30, 100},
                {INF, INF,  50, INF, INF},
                { 20, INF, INF, INF,  10},
                {INF, INF,  20, INF,  60},
                {INF, INF, INF, INF, INF}
            };

    displayMatrix(M);

    AdjList adj_list;
    adj_list = convertMatrixToList(M);
    display(adj_list);
}

