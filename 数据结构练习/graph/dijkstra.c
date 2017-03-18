#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VERTEXNUM 10


struct edge{
    int id;
    int weighted;
    struct edge *next;
};


struct vertex{
    int id;
    int indegree;
    int known;
    int weight;
    int path;
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


void CreateEdge(Graph g, int v1, int v2, int weighted)
{
    Edge e, tmp, next;
    e = malloc(sizeof(struct edge));

    e->id = v2;
    e->weighted = weighted;
    e->next = NULL;

    // Sort edge by weight.
    tmp = g[v1].first_edge;
    if(tmp != NULL)
    {
        if(tmp->weighted > e->weighted)
        {
            g[v1].first_edge = e;
            e->next = tmp;
            tmp->next = NULL;
        }
        else
        {
            while (tmp->next != NULL && e->weighted > tmp->next->weighted)
            {
                tmp = tmp->next;
            }
            e->next = tmp->next;
            tmp->next = e;
        }
    }
    else
    {
        g[v1].first_edge = e;
    }
    g[v2].indegree += 1;
}


void Dijikstra(Graph g, int id, int num)
{
    Vertex *v;
    Edge tmp;

    // Create a simple queue.
    Vertex **queue;
    int q_front = 0, q_rear = -1, q_size = 0;
    queue = malloc(sizeof(Vertex*) * num);
    memset(queue, 0, sizeof(Vertex*) * num);  // Make empty.

    // Enqueue.
    q_rear = q_rear + 1 >= num ? 0 : q_rear + 1;
    queue[q_rear] = &g[id];  // Enqueue the start vertex.
    ++q_size;

    while(q_size != 0)
    {
        // Dequeue.
        v = queue[q_front];
        q_front = q_front + 1 >= num ? 0 : q_front + 1;
        --q_size;

        v->known = 1;
        tmp = v->first_edge;
        while(tmp != NULL)
        {
            if(g[tmp->id].known == 0)
            {
                if(g[tmp->id].weight == 0 || g[tmp->id].weight > v->weight + tmp->weighted)
                {
                    if(g[tmp->id].weight == 0)
                    {
                        // Enqueue.
                        printf("I am %d.\n", g[tmp->id].id);
                        q_rear = q_rear + 1 >= num ? 0 : q_rear + 1;
                        queue[q_rear] = &g[tmp->id];
                        ++q_size;
                    }

                    g[tmp->id].weight = v->weight + tmp->weighted;
                    g[tmp->id].path = v->id;
                }
            }
            tmp = tmp->next;
        }
    }

    for(int i = 1; i < num; ++i)
    {
        if(g[i].id != id && g[i].id != 0)
        {
            printf("The shorest path length from %d vertex to %d vertex: %d\n", id, g[i].id, g[i].weight);
        }
    }

    // Destory the queue.
    free(queue);
}


int main()
{
    Graph g;

    g = Initialize(VERTEXNUM);

    CreateVertex(g, 1);
    CreateVertex(g, 2);
    CreateVertex(g, 3);
    CreateVertex(g, 4);
    CreateVertex(g, 5);
    CreateVertex(g, 6);
    CreateVertex(g, 7);

    CreateEdge(g, 1, 4, 1);
    CreateEdge(g, 1, 2, 2);

    CreateEdge(g, 2, 4, 3);
    CreateEdge(g, 2, 5, 10);

    CreateEdge(g, 3, 1, 4);
    CreateEdge(g, 3, 6, 5);

    CreateEdge(g, 4, 7, 4);
    CreateEdge(g, 4, 6, 8);
    CreateEdge(g, 4, 3, 2);
    CreateEdge(g, 4, 5, 2);

    CreateEdge(g, 5, 7, 6);

    CreateEdge(g, 7, 6, 1);

    Dijikstra(g, 1, VERTEXNUM);

    DestoryGraph(g, VERTEXNUM);

    return 0;
}
