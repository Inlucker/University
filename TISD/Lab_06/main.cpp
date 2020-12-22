#include "defines.h"
#include "structures.h"
#include "io_funcs.h"
#include "tree_funcs.h"
#include "list_funcs.h"
#include "hash_funcs.h"

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

    //print_tree_hashes(root);

    int size = count_nodes(root);

    int mas_size = size;
    bool is_simple = false;

    while (!is_simple)
    {
        mas_size++;
        is_simple = true;
        for (int i = 2; i < mas_size/2; i++)
        {
            if (mas_size % i == 0)
            {
                is_simple = false;
                break;
            }
        }
    }

    list_t *hash_table[mas_size];
    fill_hash_table(hash_table, mas_size, root);
    print_hash_table(hash_table, mas_size);

    //list_t *hash_table = create_hash_table(root);


    //hash_table_t *table = create_hash_table(root);
    //print_hash_table(table);

    //add_line_to_table(table, "lasd");

    //free_table(&table);

    delete_tree(&root);

    return 0;
}
