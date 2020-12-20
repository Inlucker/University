#include "tree_funcs.h"
#include "structures.h"

tree_node *read_file(string file_name)
{
    ifstream f(file_name);
    string input = "";
    tree_node *root = NULL;
    while(getline(f, input))
    {
        if (root == NULL)
        {
            root = create_node(input);
        }
        else
        {
            tree_node *node = create_node(input);
            add_node(root, node);
        }
    }
    return root;
}
