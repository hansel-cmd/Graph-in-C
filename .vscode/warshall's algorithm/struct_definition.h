#ifndef struct_definition_H
#define struct_definition_H

#define MAX_VERTEX 5
#define MAX 10 /** undirected: 5(5-1) / 2 **/
#define INFINITY 9999

/* An unweighted, undirected Edge */
typedef struct {
	int vertex;
	int adj_vertex;
}edgeType;

typedef struct {
	edgeType Edge[MAX];
	int edge_count;
}EdgeList;

typedef int MATRIX[MAX_VERTEX][MAX_VERTEX]; // static
typedef int ** MATRIX_1; // dynamic



#endif