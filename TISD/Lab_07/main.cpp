#include <iostream>
#include "defines.h"
#include "structures.h"

using namespace std;

int main()
{
    cout << "Hi!" << endl;

    int n = 0;
    int m = 0;

    cout << "Input file_name: ";

    string file_name = "test1.txt";
    cin >> file_name;

    rebro_t *mas = read_rebro_mas(file_name, &n, &m);
    if (mas == NULL)
    {
        cout << "Read error" << endl;
        return READ_ERROR;
    }

    graph_t *graph = create_graph(n, m, mas);

    node_t begin = 0;
    int a = 2;

    cout << "Input first node and A (max_len): ";

    cin >> begin >> a;

    node_t rez[n];
    get_nodes_mas(*graph, begin, a, rez);

    cout << "Reachable nodes: ";
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
