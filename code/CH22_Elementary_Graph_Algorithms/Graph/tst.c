#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graphs.h"

#define MAX_ADJ 3
#define MAX_V 10


int main() {
    srand(time(NULL));
    graph_t* g = graph_create(MAX_V, DIGRAPH);
    for(int  i = 0; i < MAX_V; i++) {
        while(g->vertex[i]->degree.out < MAX_ADJ){
            graph_add_edge(g, i, rand() % MAX_V);
        }
    }
    graph_adj_list_print(g);
    graph_dot_output(g, "out");
    info_t* info = bfs(g, 0);
    for(int i; i<g->n; i++){
        printf("%d <- %d, dist[%d]=%d\n", i, info->pred[i], i, info->dist[i]);
    }
    graph_destruct(g);
    return 0;
}
