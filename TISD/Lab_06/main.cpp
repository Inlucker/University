#include "defines.h"
#include "structures.h"
#include "io_funcs.h"
#include "tree_funcs.h"

int main()
{
    tree_node *root = read_file("tree22.txt");

    print_tree(root, 0);

    delete_tree(root);

    return 0;
}
