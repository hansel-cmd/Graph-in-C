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
