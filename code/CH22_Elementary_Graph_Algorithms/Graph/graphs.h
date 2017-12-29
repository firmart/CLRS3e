#ifndef GRAPHS_H
#define GRAPHS_H

/**
 * \file graphs.h
 * \brief graph definition and basic operations
 * \author Firmin MARTIN 
 * \version 0.1
 * \date 28/12/2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/** \enum type of graph*/
typedef enum {
    UNDIGRAPH, /**<  undirect graph  */
    DIGRAPH    /**<  direct graph    */
} gtype_t;

typedef struct deg_t {
    int in;   /**<  indegree  */
    int out;  /**<  outdegree  */
} deg_t;

typedef struct gvertex_t {
    int* adj_list;     /**<  adjacency list (list of vertices index)  */
    int  adj_list_len; /**<  sizeof(int) * adj_list_len bytes is reserved for adj_list  */
    deg_t degree;      /**<  indegree and outdegree  */
} gvertex_t;

typedef struct graph_t {
    gtype_t type;       /**<  graph type : undirected or directed  */
    int n;              /**<  number of vertices  */
    int m;              /**<  number of edges     */
    gvertex_t** vertex; /**<  list of vertices  */
} graph_t;

typedef struct info_t {
    int* pred;
    int* dist;
} info_t;

graph_t* graph_clone(graph_t* g);
graph_t* graph_create(int n, gtype_t type);
void graph_add_edge(graph_t* g, int u, int v);
void graph_adj_list_print(graph_t* g);
void graph_delete_adj_ele(graph_t* g, int u, int v);
void graph_destruct(graph_t* g);
void graph_dot_output(graph_t* g, char* filename);
int is_adj(graph_t* g, int u, int v);
info_t* bfs(graph_t* g, int src);

#endif  //GRAPHS_H
