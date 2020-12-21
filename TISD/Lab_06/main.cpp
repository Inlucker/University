#include "defines.h"
#include "structures.h"
#include "io_funcs.h"
#include "tree_funcs.h"
#include "list_funcs.h"

int main()
{
    list_t *list = NULL;
    add_el_to_list(&list, "lol");
    add_el_to_list(&list, "kek");
    add_el_to_list(&list, "cheburek");

    free_list(&list);

    tree_node *root = read_file("tree02.txt");

    cout << "Before balance" << endl;
    print_tree(root);

    int depth = 0;
    calculate_depth(root, &depth);
    cout << "Current depth = " << depth << endl;

    balance_tree(&root);

    cout << "After balance" << endl;
    print_tree(root);

    depth = 0;
    calculate_depth(root, &depth);
    cout << "Current depth = " << depth << endl;

    print_hash_table(root);

    delete_tree(&root);

    return 0;
}
