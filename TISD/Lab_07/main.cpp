#include <iostream>
#include "defines.h"
#include "structures.h"

using namespace std;

int main()
{
    cout << "Hi!" << endl;

    int n = 0;
    int m = 0;
    rebro_t *mas = read_rebro_mas("test2.txt", &n, &m);
    if (mas == NULL)
        return READ_ERROR;

    graph_t *graph = create_graph(n, m, mas);

    node_t begin = 0;
    int a = 2;

    node_t rez[n];
    get_nodes_mas(*graph, begin, a, rez);

    cout << "Nodes: ";
    for (int i = 0; i < n; i++)
    {
        if (rez[i])
        {
            cout << i << " ";
        }
    }
    cout << endl;

    delete [] mas;
    delete graph;

    return OK;
}
