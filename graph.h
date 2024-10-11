#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include "heap.h"

int compare(const void *a, const void *b) {
	HPair *pa, *pb;
	pa = (HPair*) a;
	pb = (HPair*) b;
	return pb->cost - pa->cost;
}

typedef struct graph {
	int V; // nr de noduri din graf
	int type; // 0 - neorientat ; 1 - orientat
	List *adjLists; // vectorul cu listele de adiacență
	int *visited; // vector pentru marcarea nodurilor vizitate
	int *start, *end;
}*Graph;

typedef struct edge {
	int u, v, cost;
} Edge;

Graph initGraph(int V, int type)
{
	Graph g;
	int i;
	g = (Graph) malloc(sizeof(struct graph));
	g->V = V;
	g->adjLists = (List*) malloc(V * sizeof(List));
	g->type = type;
	for (i = 0; i < V; i++) {
		g->adjLists[i] = NULL;
	}
	g->visited = calloc(V, sizeof(int));
	g->start = malloc(V * sizeof(int));
	g->end = malloc(V * sizeof(int));
	return g;
}

Graph insertEdge(Graph g, int u, int v, int cost)
{
	Pair p;
	p.u = u;
	p.v = v;
	p.cost = cost;

	g->adjLists[u] = addLast(g->adjLists[u], p);

	if (g->type == 0) {
		Pair p1;
		p.v = u;
		p.u = v;
		p.cost = cost;
		g->adjLists[v] = addLast(g->adjLists[v], p);
	}
	return g;
}

int isArc(Graph g, int u, int v)
{
	List tmp = g->adjLists[u];
	while (tmp != NULL) {
		if (tmp->data.v == v)
			return 1;
		tmp = tmp->next;
	}
	return 0;
}

int getCost(Graph g, int u, int v)
{
	List tmp = g->adjLists[u];
	while (tmp != NULL) {
		if (tmp->data.v == v)
			return tmp->data.cost;
		tmp = tmp->next;
	}
	return 999999;
}

Graph freeGraph(Graph graph)
{
	int i;
	if (!graph)
		return graph;
	if (graph->visited)
		free(graph->visited);
	if (graph->start)
		free(graph->start);
	if (graph->end)
		free(graph->end);
	if (graph->adjLists) {
		for (i = 0; i < graph->V; i++)
			graph->adjLists[i] = freeList(graph->adjLists[i]);
		free(graph->adjLists);
	}
	free(graph);
	return NULL;
}
List Prim(Graph g, int start) {
	List result = NULL;

	Heap h = initHeap(compare);
	HPair pair;
	int *d = malloc(g->V * sizeof(int));
	int *P = malloc(g->V * sizeof(int));
	pair.node = start;
	pair.cost = 0;
	h = insertHeap(h, pair);
	// TODO 2
	for(int i=0;i<g->V;++i){
		d[i] = 9999999;
		P[i] = NULL;
	}
	d[start] = 0;
	int cnt = 0;
	while(!isEmptyHeap(h)){
		HPair u = extractMin(h);
		if(g->visited[u.node]== 0){
			g->visited[u.node] = 1;
			if(isArc(g, u.node, P[u.node])){
				V data;
				data.u = u.node;
				data.v = P[u.node];
				data.cost = getCost(g, u.node, P[u.node]);
				result = addLast(result, data);
			}
		}
		for(int i=0;i<g->V;++i){
			if(isArc(g,u.node,i)){
				if(d[i]> d[u.node] + getCost(g, u.node, i))
				{
					d[i] = d[u.node] + getCost(g, u.node, i);
					P[i] = u.node;
					HPair p;
					p.node = i;
					p.cost = d[i];
					insertHeap(h, p);
				}
			}
		}
		cnt++;
	}
	free(P);
	free(d);
	h = freeHeap(h);
	return result;
}