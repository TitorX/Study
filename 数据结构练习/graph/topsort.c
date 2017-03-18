#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERTEXNUM 10

struct edge{
    int id;
    struct edge *next;
};

struct vertex{
    int id;
    int indegree;
    struct edge *first_edge;
};

typedef struct edge *Edge;
typedef struct vertex Vertex;
typedef struct vertex *Graph;


Graph Initialize(int num)
{
    Graph g;
    g = malloc(sizeof(Vertex) * (num + 1));
    memset(g, 0, sizeof(Vertex) * (num + 1));

    return g;
}


void DestoryGraph(Graph g, int num)
{
    Edge tmp1, tmp2;
    for(int i = 1; i <= num; ++i)
    {
        tmp1 = g[i].first_edge;
        while(tmp1 != NULL)
        {
            tmp2 = tmp1;
            tmp1 = tmp2->next;
            free(tmp2);
        }
    }
    free(g);
}


void CreateVertex(Graph g, int id)
{
    g[id].id = id;
}


void CreateEdge(Graph g, int v1, int v2)
{
    Edge e, tmp;
    e = malloc(sizeof(struct edge));

    e->id = v2;
    e->next = NULL;

    tmp = g[v1].first_edge;
    if(tmp != NULL)
    {
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = e;
    }
    else
    {
        g[v1].first_edge = e;
    }
    g[v2].indegree += 1;
}


int TopSort(Graph g, int num)
{
    Vertex *v;
    Edge tmp;
    int count = 0;
    int vertex_num = 0;

    // Create a simple queue.
    Vertex **queue;
    int q_front = 0, q_rear = -1, q_size = 0;
    queue = malloc(sizeof(Vertex*) * num);
    memset(queue, 0, sizeof(Vertex*) * num);  // Make empty.

    for(int i = 1; i <= num; ++i)
    {
        v = &g[i];
        if(v->id != 0)
        {
            vertex_num += 1;
            if(v->indegree == 0)
            {
                // Enqueue.
                q_rear = q_rear + 1 >= num ? 0 : q_rear + 1;
                queue[q_rear] = v;
                ++q_size;
            }
        }
    }

    while(q_size != 0)
    {
        // Dequeue.
        v = queue[q_front];
        q_front = q_front + 1 >= num ? 0 : q_front + 1;
        --q_size;
        ++count;

        tmp = v->first_edge;
        while(tmp != NULL)
        {
            if(--g[tmp->id].indegree == 0)
            {
                // Enqueue.
                q_rear = q_rear + 1 >= num ? 0 : q_rear + 1;
                queue[q_rear] = &g[tmp->id];
                ++q_size;
            }
            tmp = tmp->next;
        }
    }

    // Destory the queue.
    free(queue);

    return count == vertex_num;
}


int main()
{
    Graph g;

    g = Initialize(VERTEXNUM);

    CreateVertex(g, 1);
    CreateVertex(g, 2);
    CreateVertex(g, 3);
    CreateEdge(g, 1, 2);
    CreateEdge(g, 2, 3);
    CreateEdge(g, 3, 1);

    for(int i = 1; i <= VERTEXNUM; ++i)
    {
        printf("(%d, %d) ", g[i].id, g[i].indegree);
    }
    puts("");

    if(TopSort(g, VERTEXNUM))
    {
        puts("Graph hasn't a cycle!");
    }
    else
    {
        puts("Graph has a cycle!");
    }

    DestoryGraph(g, VERTEXNUM);

    return 0;
}
