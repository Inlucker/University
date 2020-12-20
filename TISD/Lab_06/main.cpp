#include "defines.h"
#include "structures.h"
#include "io_funcs.h"
#include "tree_funcs.h"

int main()
{
    tree_node *root = read_file("tree01.txt");

    delete_tree(root);

    return 0;
}
