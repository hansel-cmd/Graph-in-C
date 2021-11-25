#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// This traversal is only for directed graphs (digraphs.)
// This traversal follows the recursive approach.
// Your task is to create non-recursive function for DFS. 
//           Hint: Use the stack data structure. 
//If finished, check out solution.c

// constraint/s:
//      This list is an unweighted, directed graph.
//      Graph's representation is Adjacency List.
//      Graph is statically defined.

/* Data Structure Definition */

#define MAX_VERTEX 9
// n(n - 1) // we dont divide this by 2
// because this is an undirected graph.
#define MAX_EDGES 72

typedef struct {
    int u;
    int v;
} Edge;

typedef struct {
    Edge edge[MAX_EDGES];
    int edge_count;
} EdgeList;

typedef struct node {
    int adj_vertex;
    struct node *next;
} node, *nodePtr;

typedef nodePtr Graph[MAX_VERTEX]; // static

void populateGraph(Graph G, EdgeList E)
{
    // initialize this to avoid bug
    for (int i = 0; i < MAX_VERTEX; i++)
        G[i] = NULL;

    for (int i = 0; i < E.edge_count; i++) {
        int u = E.edge[i].u;
        int v = E.edge[i].v;

        nodePtr *trav;
        trav = &G[u];
        while (*trav) trav = &(*trav)->next;
        
        *trav = (nodePtr) calloc (1, sizeof(node));
        if (*trav) (*trav)->adj_vertex = v;
    }
}

void DFS(Graph G)
{
    // todo
}

void displayGraph(Graph G)
{
    for (int i = 0; i < MAX_VERTEX; i++) {
        printf("\n%d: ", i);
        nodePtr trav;
        trav = G[i];
        while (trav) {
            printf("%d ", trav->adj_vertex);
            trav = trav->next;
        }
    }
}

int main()
{
    EdgeList E = {
        {{0, 1}, {0, 3}, {0, 4},
        {1, 5},
        {2, 1}, {2, 3},
        {3, 2},
        {4, 7},
        {5, 8}, {5, 6},
        {6, 2},
        {8, 7}},
        12
    };
    Graph G;
    populateGraph(G, E);

    /* =------------------------------------------------= */
    displayGraph(G);

    DFS(G);

    return 0;
}



