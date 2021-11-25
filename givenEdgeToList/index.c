#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** 
	1. Given an edgeList, create the Adjacency List to be returned to the
		calling function, and
	2. Display the List in a table form...

**/

#define MAX_VERTEX 5
// 10 edges because n(n - 1)/2 = 5(4)/2 = 10 
// we divide 2 because this is an undirected graph.
#define MAX 10

// An unweighted, undirected graph
typedef struct {
    int vertex;
    int adj_vertex;
} edgeType;

typedef struct {
    edgeType Edge[MAX];
    int edge_count;
} EdgeList;

typedef struct node {
    int vertex;
    struct node *next;
} node, *nodePtr;

typedef nodePtr *AdjList; // dynamic

AdjList createAdjacencyList(EdgeList E)
{
    AdjList adj_list;
    adj_list = (AdjList) calloc (MAX_VERTEX, sizeof(node));
    if (adj_list) {

        nodePtr *trav;
        for (int i = 0; i < E.edge_count; i++) {
            
            // get the vertex and adjacent vertex
            int u = E.Edge[i].vertex;
            int v = E.Edge[i].adj_vertex;

            // traverse until the end of u
            trav = &adj_list[u];
            while (*trav) trav = &(*trav)->next;

            // insert its adjacent vertex
            *trav = (nodePtr) calloc (1, sizeof(node));
            if (*trav) (*trav)->vertex = v;

            // traverse until the end of v
            trav = &adj_list[v];
            while (*trav) trav = &(*trav)->next;

            // insert its adjacent vertex
            *trav = (nodePtr) calloc (1, sizeof(node));
            if (*trav) (*trav)->vertex = u;
        }
    }
    return adj_list;
}

void displayAdjacencyList(AdjList adj_list)
{
    // table format
    for (int i = 0; i < MAX_VERTEX; i++) {
        printf("\n%d : ", i);

        nodePtr trav;
        trav = adj_list[i];
        while (trav) {
            printf("%2d ", trav->vertex);
            trav = trav->next;
        }
    }
}

int main()
{
	EdgeList E = {
				{{0,1},{0,2},{0,3},{0,4},
					{1,2},{2,3},{2,4},{3,4}}, 
				8
				};
	
	AdjList List;
	List = createAdjacencyList(E);
	
	displayAdjacencyList(List);
	return 0;
}
