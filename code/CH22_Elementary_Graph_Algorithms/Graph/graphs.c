/**
 * \file graphs.c
 * \brief graph's basic operations implementation
 * \author Firmin MARTIN
 * \version 0.1
 * \date 28/12/2017
 */

#include "graphs.h"
#include "queue.h"
#include "stack.h"

/**
 * Create a graph initialized as a forest with n vertices
 * \param n    number of vertices
 * \param type type of graph (digraph, undigraph)
 * \return return a graph initialized as a forest
 */
graph_t* graph_create(int n, gtype_t type) {
    graph_t* g;
    g = (graph_t*) malloc(sizeof(graph_t));
    assert(g);
    if (g != NULL) {
        g->type = type;  /* initialize type of graph */
        g->n = n;        /* initialize number of vertices */
        g->m = 0;        /* g is a forest => 0 edge */
        g->vertex = (gvertex_t**) malloc(sizeof(gvertex_t*) * n);
        assert(g->vertex);
        for(int i = 0; i < g->n ; i++) {
            g->vertex[i] = (gvertex_t*) malloc(sizeof(gvertex_t));
            assert(g->vertex[i]);
            /* initialize an array with size 5 by default */
            g->vertex[i]->adj_list = (int*) malloc(sizeof(int) * 5);
            assert(g->vertex[i]->adj_list);
            g->vertex[i]->adj_list_len = 5;
            /* g is a forest => deg_in(i) = deg_out(i) = 0 */
            g->vertex[i]->degree.in = 0;
            g->vertex[i]->degree.out = 0;
        }
    }
    return g;
}

/**
 * Free a graph
 * \param g a graph
 */
void graph_destruct(graph_t* g) {
    for (int i = 0; i < g->n ; i++) {
        free(g->vertex[i]->adj_list);
        free(g->vertex[i]);
    }
    free(g->vertex);
    free(g);
}

/**
 * Determinate if v is in the adjacency list of u in graph g
 * \param g graph
 * \param u vertex index
 * \param v vertex index
 */
int is_adj(graph_t* g, int u, int v) {
    gvertex_t* v_u = g->vertex[u];
    assert(v_u);
    for(int i = 0; i < v_u->degree.out; i++) {
        if(v_u->adj_list[i] == v) return 1;
    }
    return 0;
}

/**
 * Add the edge \f$(u,v)\f$ in the graph \f$g\f$. If \f$g\f$ is an undigraph, \f$(v,u)\f$ is also added.
 * \param g graph
 * \param u vertex index
 * \param v vertex index
 */
void graph_add_edge(graph_t* g, int u, int v) {
    gvertex_t *v_u = g->vertex[u], *v_v = g->vertex[v];
    assert(u >= 0 && v >= 0 && u < g->n && v < g->n);
    assert(v_u->degree.out <= v_u->adj_list_len);
    if (is_adj(g, u, v)) return ;
    if (v_u->degree.out == v_u->adj_list_len) {
        int* newlist = realloc(v_u->adj_list, sizeof(int) * (v_u->adj_list_len + 10));
        assert(newlist);
        v_u->adj_list = newlist;
        v_u->adj_list_len += 10;
    }
    v_u->adj_list[v_u->degree.out] = v;
    v_u->degree.out++;
    v_v->degree.in++;
    if (g->type == UNDIGRAPH && u != v) {
        assert(v_v->degree.out <= v_v->adj_list_len);
        if (v_v->degree.out == v_v->adj_list_len) {
            int* newlist = realloc(v_v->adj_list, sizeof(int) * (v_v->adj_list_len + 10));
            assert(newlist);
            v_v->adj_list = newlist;
            v_v->adj_list_len += 10;
        }
        v_v->adj_list[v_v->degree.out] = u;
        v_v->degree.out++;
        v_u->degree.in++;
    }
    g->m++;
}

/**
 * Print graph's adjacency list representation
 * \param g graph
 */
void graph_adj_list_print(graph_t* g) {
    if (g->type == DIGRAPH) printf("type : digraph\n");
    else if (g->type == UNDIGRAPH) printf("type : undigraph\n");
    printf("n=%d, m=%d\n", g->n, g->m);
    for(int i = 0; i < g->n; i++) {
        printf("[%d] ", i);
        if (g->vertex[i]->degree.out > 0) printf("-> ");
        for(int j = 0; j < g->vertex[i]->degree.out ; j++) {
            printf("[%d]", g->vertex[i]->adj_list[j]);
        }
        printf("\n");
    }
}

/**
 * Clone a graph
 * \param g graph
 * \return graph cloned
 * \bug sizeof(pt) is wrong!!
 */
graph_t* graph_clone(graph_t* g) {
    graph_t* new_g;
    new_g = (graph_t*) malloc(sizeof(graph_t));
    if (new_g != NULL) {
        new_g->type = g->type;
        new_g->n = g->n;
        new_g->m = g->m;
        new_g->vertex = (gvertex_t**) malloc(sizeof(g->vertex));
        assert(new_g->vertex);
        for(int i = 0; i < g->n ; i++) {
            new_g->vertex[i] = (gvertex_t*) malloc(sizeof(gvertex_t));
            assert(g->vertex[i]);
            new_g->vertex[i]->adj_list = (int*) malloc(sizeof(g->vertex[i]->adj_list));
            assert(new_g->vertex[i]->adj_list);
            new_g->vertex[i]->adj_list_len = g->vertex[i]->adj_list_len;
            new_g->vertex[i]->degree.in = g->vertex[i]->degree.in;
            new_g->vertex[i]->degree.out = g->vertex[i]->degree.out;
        }
    }
    return new_g;
}

/**
 * Delete the edge (u,v) in graph g. If g is an undigraph, (v,u) is also removed.
 * \param g graph
 * \param u vertex index
 * \param v vertex index
 */
void graph_delete_adj_ele(graph_t* g, int u, int v) {
    gvertex_t *v_u = g->vertex[u], *v_v = g->vertex[v];
    assert(v_u && v_v);
    int flag = 0;
    for (int i = 0; i < v_u->degree.out; i++) {
        if(v_u->adj_list[i] == v) {
            flag = 1;
            for (int j = i; j < v_u->degree.out - 1; j++) {
                v_u->adj_list[j] = v_u->adj_list[j + 1];
            }
            v_u->degree.out--;
        }
    }
    if (g->type == UNDIGRAPH && flag) {
        for (int i = 0; i < v_v->degree.out; i++) {
            if(v_v->adj_list[i] == u) {
                for (int j = i; j < v_v->degree.out - 1; j++) {
                    v_v->adj_list[j] = v_v->adj_list[j + 1];
                }
                v_v->degree.out--;
            }
        }
    }
    if(flag) g->m--;
}

/**
 * Output the graph g in dot format (filename.dot) and use dot compile it to filename.ps .
 * \param g graph
 * \param filename filename without any extension
 * \todo system call ?
 */

void graph_dot_output(graph_t* g, char* filename) {
    FILE* pfile;
    pfile = fopen(filename, "w");
    if (pfile == NULL) perror ("Error opening file");
    if (g->type == DIGRAPH) {
        fprintf(pfile, "digraph g {\nnode [shape=\"circle\"];\n");
        for(int i = 0; i < g->n; i++) {
            if(g->vertex[i]->degree.out == 0) fprintf(pfile, "%d;\n", i);
            for(int j = 0; j < g->vertex[i]->degree.out ; j++) {
                fprintf(pfile, "%d -> %d;\n", i, g->vertex[i]->adj_list[j]);
            }
        }
    } else if (g->type == UNDIGRAPH) {
        fprintf(pfile, "graph g {\nnode [shape=\"circle\"];\n");
        for(int i = 0; i < g->n; i++) {
            if(g->vertex[i]->degree.out == 0) fprintf(pfile, "%d;\n", i);
            for(int j = 0; j < g->vertex[i]->degree.out ; j++) {
                if(i <= g->vertex[i]->adj_list[j]) {
                    fprintf(pfile, "%d -- %d;\n", i, g->vertex[i]->adj_list[j]);
                }
            }
        }
    }
    fprintf(pfile, "}\n");
    fclose(pfile);
    //system(strcat(strcat(strcat(strcat("dot ", filename),"-Tps -o "),filename),".ps"));
}

int* inttoptr(int i){
    int* ptr = malloc(sizeof(int));
    *ptr = i;
    return ptr;
}

info_t* bfs(graph_t* g, int src) {
    int* color = malloc(g->n * sizeof(int));
    int* pred  = malloc(g->n * sizeof(int));
    int* dist  = malloc(g->n * sizeof(int));
    assert(color && pred && dist);
    for(int i = 0; i < g->n; i++) {
        color[i] = 0;
        pred[i] = -1;
        dist[i] = g->n + 1;
    }
    queue_t* q = queue_create(sizeof(int), g->n);
    assert(q);
    int i = src;
    for (int j = 0; j < g->n; j++) {
        if (color[i] == 0) {
            color[i] = 1;
            dist[i] = 0;
            pred[i] = -1;
            queue_enqueue(q, inttoptr(i));
            while(!queue_isempty(q)) {
                int* u = queue_dequeue(q);
                for(int k = 0; k < g->vertex[*u]->degree.out; k++) {
                    if (color[k] == 0) {
                        color[k] = 1;
                        dist[k] = dist[*u] + 1;
                        pred[k] = *u;
                        queue_enqueue(q, inttoptr(k));
                    }
                }
                color[*u] = 2;
            }
        }
        i = j;
    }
    free(color);
    info_t* info = malloc(sizeof(info_t));
    info->dist = dist;
    info->pred = pred;
    queue_destruct(q);
    return info;
}
