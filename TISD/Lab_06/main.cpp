#include "defines.h"
#include "structures.h"
#include "io_funcs.h"
#include "tree_funcs.h"

int main()
{
    tree_node *root = read_file("tree02.txt");

    //cout << "Before delete 'eyebrow'" << endl;
    cout << "Before balance" << endl;
    print_tree(root);

    balance_tree(&root);

    cout << "After balance" << endl;
    print_tree(root);

    //int nodes_number = count_nodes(root);
    //cout << "Nodes number is: " << nodes_number << endl;

    //tree_node *test = get_new_root(root);
    //cout << "New root ptr: " << test << endl;

    //tree_node *test = search_node(root, "exception");
    //void *ptr_to_delete = search_node(root, "exception");
    //delete test;

    //cout << search_node(root, "exception") << " " << test << endl;
    //tree_node **node_to_delete = search_node(&root, "eyebrow");
    //tree_node **node_to_null = search_node(root, "eyebrow");
    //cout << node_to_delete << " points on " << *node_to_delete << endl;

    /*cout << "Print tree 'paralyzed'" << endl;
    print_tree(*search_node(&root, "paralyzed"));

    delete_tree(search_node(&root, "eyebrow"));


    cout << "After delete 'eyebrow'" << endl;
    print_tree(root);*/

    delete_tree(&root);

    return 0;
}
