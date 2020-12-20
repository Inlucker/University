#include "defines.h"
#include "structures.h"
#include "io_funcs.h"
#include "tree_funcs.h"

int main()
{
    tree_node *root = read_file("tree22.txt");

    cout << "Before delete 'eyebrow'" << endl;
    print_tree(root, 0);

    //tree_node *test = search_node(root, "exception");
    //void *ptr_to_delete = search_node(root, "exception");
    //delete test;

    //cout << search_node(root, "exception") << " " << test << endl;
    //tree_node **node_to_delete = search_node(&root, "eyebrow");
    //tree_node **node_to_null = search_node(root, "eyebrow");
    //cout << node_to_delete << " points on " << *node_to_delete << endl;
    delete_tree(search_node(&root, "eyebrow"));


    cout << "After delete 'eyebrow'" << endl;
    print_tree(root, 0);

    delete_tree(&root);

    return 0;
}
