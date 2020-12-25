#include "structures.h"
#include <iostream>
#include <fstream>
#include <queue>

//using namespace std;

/*rebro_t *create_rebro(int a, int b)
{
    rebro_t *new_rebro = new rebro_t;
    new_rebro->a = a;
    new_rebro->b = b;
    return new_rebro;
}*/

rebro_t create_rebro(int a, int b)
{
    rebro_t new_rebro;
    new_rebro.a = a;
    new_rebro.b = b;
    return new_rebro;
}

rebro_t *read_rebro_mas(string file_name, int *node_n, int *rebro_n)
{
    rebro_t *rez = NULL;
    *node_n = 0;
    ifstream file(file_name);
    if (file.is_open())
    {
        string input = "";
        if (file >> *node_n >> *rebro_n)
        {
            rez = new rebro_t[*rebro_n];
            int i = 0;
            int tmp_a = -1, tmp_b = -1;
            while(file >> tmp_a >> tmp_b && tmp_a >= 0 && tmp_b >= 0)
            {
                rez[i] = create_rebro(tmp_a, tmp_b);
                i++;
            }
            if (i > *rebro_n)
            {
                delete [] rez;
                rez = NULL;
                *node_n = -1;
            }
        }
    }
    return rez;
}

graph_t *create_graph(int n, int m, rebro_t *rebro_mas)
{
    graph_t *new_graph = new graph_t;
    new_graph->node_amount = n;
    new_graph->rebro_amount = m;
    new_graph->rebro_mas = rebro_mas;
    return new_graph;
}

bool check_node(graph_t graph, node_t start, int max_a)
{
    queue<node_t> frontier;
}

void get_nodes_mas(graph_t graph, node_t begin, int a, node_t rez[])
{
    int n = graph.node_amount;

    for (int i = 0; i < n; i++)
    {
        rez[i] = 0;
    }

    if (graph.rebro_mas && n != 0)
    {
        int m = graph.rebro_amount;
        rebro_t *mas = graph.rebro_mas;

        queue<elem_t> frontier;
        elem_t start;
        start.node = begin;
        start.cur_len = 0;
        frontier.push(start);
        elem_t current;
        int cur_len = 0;

        while (!frontier.empty())
        {
            current = frontier.front();
            node_t node = current.node;
            cur_len = current.cur_len;
            if (rez[node] == 0 && cur_len <= a)
            {
                for (int i = 0; i < m; i++)
                {
                    if (mas[i].a == node)
                    {
                        elem_t next;
                        next.node = mas[i].b;
                        next.cur_len = cur_len + 1;
                        frontier.push(next);
                    }
                }

                rez[node] = 1;
            }

            frontier.pop();
        }


    }
}

