#ifndef STRUCTURES_H
#define STRUCTURES_H

//#include <queue>
#include <string>

using namespace std;

typedef int node_t;

struct elem_t
{
    node_t node;
    int cur_len;
};

struct rebro_t
{
    node_t a;
    node_t b;
};

struct graph_t
{
    int node_amount;
    int rebro_amount;
    rebro_t *rebro_mas;
};

rebro_t create_rebro(int a, int b);

rebro_t *read_rebro_mas(string file_name, int *node_n, int *rebro_n);

graph_t *create_graph(int n, int m, rebro_t *rebro_mas);

void get_nodes_mas(graph_t graph, node_t begin, int a, node_t rez[]);

#endif // STRUCTURES_H
