#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// This is the DFS List Traversal following the Iterative Approach.
// This traversal is only for directed graphs (digraphs.)

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

void DFS(Graph G, int starting_point)
{
    // initialize all vertices to be unvisited
    int visited[MAX_VERTEX];
    memset(visited, 0, sizeof(visited));

    // we set this node as visited
    visited[starting_point] = 1;
    printf("%d ", starting_point);

    // Using stack data structure
    int STACK[1000];
    int top = -1;

    STACK[++top] = starting_point;

    // If stack is not yet empty
    // there is/are still node/s left to explore
    while (top >= 0) {

        // we pop the node from the stack
        int current_vertex = STACK[top--];

        // If the current_vertex is not yet visited,
        // we mark that as visited
        if (!visited[current_vertex]) {
            visited[current_vertex] = 1;
            printf("%d ", current_vertex);
        }

        // From this vertex, we explore deeper
        int temp_stack[1000];
        int temp_top = -1;
        for (nodePtr trav = G[current_vertex]; 
                trav != NULL; trav = trav->next) {
            // we insert to a temp_stack all the
            // adjacent_vertex of the current_vertex.
            // This sounds like a BFS, the difference is
            // that we use a stack.
            if (!visited[trav->adj_vertex])
                temp_stack[++temp_top] = trav->adj_vertex;
        }

        // the first node that was inserted in the temp_stack
        // should be the first node that we need to explore
        // from the original stack. (Why?)
        // The first node that was inserted from the temp_stack
        // is the FIRST adjacent node of the current_vertex
        // And that is where we should explore first.
        while (temp_top >= 0) STACK[++top] = temp_stack[temp_top--];
    }


/**
 *
 *          On Line 95, we can actually just push everything
 *          directly from the original STACK. And if we do that,
 *          we should remove the while loop on line 105.
 * 
 *          The only reason we did the loop on line 105 was to
 *          correctly insert the adj vertex of the current vertex.
 * 
 *          Now, doing so yields different DFS result. HOWEVER,
 *          the DFS result is STILL VALID.
 * 
 *          One more reason we are using temp_stack and the loop on
 *          line 105 was only so that we have the same DFS result
 *          if we were to do a RECURSIVE approach.
 * 
**/

    
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
    printf("\n");
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

    int starting_point = 0;
    // This is using iterative method.
    DFS(G, starting_point);

    return 0;
}




