#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// BFS Recursive Traversal on an Adjacency List Representation.
// Although unnatural, it is not impossible.

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

typedef struct queue {
        int q[1000];
        int rear;
        int front;
}Queue;

void BFS(Graph G, Queue *q, int visited[], int current_node)
{
    // mark the current node as visited
    visited[current_node] = 1;
    printf("%d ", current_node);

    // from the current node, get ALL the
    // adjacent vertices
    nodePtr trav;
    trav = G[current_node];
    while (trav) {
        // if the adjacent vertex of the current node
        // is not yet visited, then insert that into the queue
        if (!visited[trav->adj_vertex])
            q->q[++q->rear] = trav->adj_vertex;
        trav = trav->next;
    }

    // if queue is not yet empty,
    // there is/are still node/s left to visit
    if (q->front <= q->rear) {
        // dequeue to get the first adjacent vertex
        int adjacent_vertex = q->q[q->front++];
        // perform BFS to the adjacent vertex
        BFS(G, q, visited, adjacent_vertex);
    }
}

void BFSTraversal(Graph G, int starting_point)
{
    Queue q;
    q.front = 0;
    q.rear = -1;

    int visited[MAX_VERTEX];
    memset(visited, 0, sizeof(visited));

    BFS(G, &q, visited, starting_point);
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
    BFSTraversal(G, starting_point);

    return 0;
}