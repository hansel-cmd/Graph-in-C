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
    printf("%3c", ' ');
    for (int i = 0; i < MAX_VERTEX; i++)
        printf("%3d ", i);


	for (int i = 0; i < MAX_VERTEX; i++) {
		printf("\n%d: ", i);
		for (int j = 0; j < MAX_VERTEX; j++)
			M[i][j] == INF ? printf("%3c ", 236) : printf("%3d ", M[i][j]);
		printf("\n");
	}
}

AdjList convertMatrixToList(MATRIX M)
{
    AdjList adj_list;
    adj_list = (AdjList) calloc (MAX_VERTEX, sizeof(nodePtr));
    if (adj_list) {
        
        // loop matrix to get (u, v)
        for (int u = 0; u < MAX_VERTEX; u++) {
            for (int v = 0; v < MAX_VERTEX; v++) {
                
                // if there is an edge,
                // we add that to the adj list
                // M[u][v] is also the weight.
                if (M[u][v] != INF) {

                    // traverse until the end of u
                    nodePtr *trav;
                    trav = &adj_list[u];
                    while (*trav) trav = &(*trav)->next;

                    *trav = (nodePtr) calloc (1, sizeof(node));
                    if (*trav) {
                        (*trav)->adj_vertex = v;
                        (*trav)->weight = M[u][v];
                    }
                }
            }
        }
    }
    return adj_list;
}

void displayAdjList(AdjList adj_list)
{
    printf("\nadj_vertex(weight)");
    for (int i = 0; i < MAX_VERTEX; i++) {

        printf("\n%d: ", i);
        nodePtr trav;
        trav = adj_list[i];
        while (trav) {
            printf("%d(%d) ", trav->adj_vertex, trav->weight);
            trav = trav->next;
        }
    }
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
    displayAdjList(adj_list);

    /** 
				Expected Output for Matrix
				{INF,  10, INF, 30, 100},
				{INF, INF,  50, INF, INF},
				{ 20, INF, INF, INF, 10},
				{INF, INF,  20, INF, 60},
				{INF, INF, INF, INF, INF}
                
                =----------------------------=

                Expected Output for List
				0 -> 1(10) -> 3(30) -> 4(100)
                1 -> 2(50)
                2 -> 0(20) -> 4(10)
                3 -> 2(20) -> 4(60)
                4
	**/
}

