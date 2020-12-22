#include "defines.h"
#include "structures.h"
#include "io_funcs.h"
#include "tree_funcs.h"
#include "list_funcs.h"
#include "hash_funcs.h"

int main()
{
    tree_node *root = read_file("tree02.txt");

    cout << "Line in fille 'tree02.txt' for word 'exception' = " << search_word_in_file("tree02.txt", "exception") << endl;

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

    // Hash table creationg start
    int size = count_nodes(root);

    int mas_size = make_simple(size);

    list_t *hash_table[mas_size];
    fill_hash_table(hash_table, mas_size, root, my_hash2);
    print_hash_table(hash_table, mas_size, my_hash2);

    cout << "Hash for word 'exception' = " << search_word_in_hash_table(hash_table, mas_size, "exception", my_hash2);

    free_hash_table(hash_table, mas_size);
    // Hash table creationg end

    delete_tree(&root);

    return 0;
}
