#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graphs.h"


int main(int argc, char** argv) {
    printf("%d\n",argc);
    int max_v = argc >= 2 ? atoi(argv[1]) : 10;
    int max_adj = argc >= 3 ? atoi(argv[2]) : 2;
    gtype_t t = argc >= 4 ? (atoi(argv[3]) == 0 ? UNDIGRAPH : DIGRAPH) : UNDIGRAPH;
    assert(max_adj <= max_v);
    srand(time(NULL));
    graph_t* g = graph_create(max_v, t);
    for(int  i = 0; i < max_v; i++) {
        while(g->vertex[i]->degree.out < rand()%(max_adj+1)+(t==UNDIGRAPH?0:1)) {
            graph_add_edge(g, i, rand() % max_v);
        }
    }
    graph_adj_list_print(g);
    info_t* info = bfs(g, 0);
    for(int i; i < g->n; i++) {
        printf("%d <- %d, dist[%d]=%d\n", i, info->pred[i], i, info->dist[i]);
    }
    graph_search_dot_output(g, info, "out");
    graph_destruct(g);
    info_destruct(info);
    return 0;
}
