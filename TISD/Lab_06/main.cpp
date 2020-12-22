#include "defines.h"
#include "structures.h"
#include "io_funcs.h"
#include "tree_funcs.h"
#include "list_funcs.h"
#include "hash_funcs.h"
#include "get_ticks.h"

#define MAX_SIZE_OF_HASH_TABLE 100000

int main()
{
    /*tree_node *test_root = read_file("test2.txt");

    cout << "Line in fille 'tree02.txt' for word 'eyebrow' = " << search_word_in_file("tree02.txt", "eyebrow") << endl;

    cout << "Before balance" << endl;
    print_tree(test_root);

    balance_tree(&test_root);

    cout << "After balance" << endl;
    print_tree(test_root);

    tree_node **word = search_word_in_tree(&test_root, "eyebrow");

    cout << "Word '" << (*word)->value << "' in tree have left " << (*word)->left << " ptr and right " << (*word)->right << " ptr." << endl;
    if ((*word)->left)
        cout << "Left word: " << (*word)->left->value << endl;
    if ((*word)->right)
        cout << "Right word: " << (*word)->right->value << endl;

    // Hash table creationg start
    int size = count_nodes(test_root);

    int mas_size = make_simple(size);

    list_t *hash_table[mas_size];
    fill_hash_table(hash_table, mas_size, test_root, my_hash2);
    print_hash_table(hash_table, mas_size, my_hash2);

    cout << "Hash for word 'eyebrow = " << search_word_in_hash_table(hash_table, mas_size, "eyebrow", my_hash2);

    free_hash_table(hash_table, mas_size);
    // Hash table creationg end

    delete_tree(&test_root);*/

    //Menu start
    srand(time(0));

    //HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    int input = -1;

    tree_node *root = read_file("test2.txt");

    while (input != 0)
    {
        cout << endl;
        cout << "Mas_stack commands:" << endl;
        cout << "1 - Read tree from file" << endl;
        cout << "2 - Print tree" << endl;
        cout << "3 - Balance tree" << endl;
        cout << "4 - Search word in tree" << endl;
        cout << "5 - Delete word from tree" << endl;
        cout << "6 - Add word to tree" << endl;
        cout << "7 - Create, print and search hash table" << endl;
        cout << "8 - Search word in file" << endl;
        cout << "9 - Time tests" << endl;
        cout << "10 - Memory tests" << endl;
        cout << "0 - Exit from programm\n" << endl;

        _flushall();
        cout << "Enter the number of command to be done: ";
        while (!(cin >> input))
        {
            cout << "Wrong input" << endl;
            cin.clear();
            _flushall();
            cout << "Enter the number of command to be done: ";
        }

        switch (input)
        {
        case 1:
        {
            _flushall();
            cout << "Enter the file name: ";
            string file_name;
            getline(cin, file_name);
            tree_node *tmp_root = read_file(file_name);
            if (tmp_root)
                root = tmp_root;
            else
                cout << "No such file" << endl;
            break;
        }
        case 2:
        {
            print_tree(root);
            break;
        }
        case 3:
        {
            balance_tree(&root);
            cout << "Balanced tree: " << endl;
            print_tree(root);
            break;
        }
        case 4:
        {
            _flushall();
            cout << "Enter the word: ";
            string word;
            getline(cin, word);
            int comp_counter = 0;
            tree_node **node = search_word_in_tree(&root, word, &comp_counter);
            if (node)
            {
                cout << "Word '" << (*node)->value << "' in tree have left " << (*node)->left << " ptr and right " << (*node)->right << " ptr." << endl;
                if ((*node)->left)
                    cout << "Left word: " << (*node)->left->value << endl;
                if ((*node)->right)
                    cout << "Right word: " << (*node)->right->value << endl;
                print_searched_word_in_tree(root, word);
                cout << "Compare number: " << comp_counter << endl;
            }
            else
            {
                cout << "No such word in tree" << endl;
            }
            break;
        }
        case 5:
        {
            _flushall();
            cout << "Enter the word: ";
            string word;
            getline(cin, word);
            int comp_counter = 0;
            tree_node **node = search_word_in_tree(&root, word, &comp_counter);
            if (*node)
            {
                cout << "Deleted this part: " << endl;
                cout << "\x1b[31m";
                print_tree(*node);
                cout << "\x1b[0m";
                delete_tree(node);
                print_tree(root);
            }
            else
            {
                cout << "No such word in tree" << endl;
            }
            break;
        }
        case 6:
        {
            _flushall();
            cout << "Enter the word: ";
            string word;
            getline(cin, word);
            tree_node *tmp = create_node(word);
            add_node(root, tmp);
            balance_tree(&root);
            print_searched_word_in_tree(root, word);
            break;
        }
        case 7:
        {
            if (root)
            {
                _flushall();
                cout << "Enter the word: ";
                string word;
                getline(cin, word);
                _flushall();
                cout << "Enter the max compares number: ";
                int max_comp;
                cin >> max_comp;

                if (max_comp <= 0)
                {
                    cout << "Wrong input" << endl;
                    break;
                }

                int size = count_nodes(root);

                int mas_size = size;
                int comp_number = 100;
                while (comp_number > max_comp && mas_size <= MAX_SIZE_OF_HASH_TABLE)
                {
                    mas_size = make_simple(mas_size);
                    list_t *hash_table[mas_size];
                    fill_hash_table(hash_table, mas_size, root, my_hash2);
                    comp_number = count_max_comp(hash_table, mas_size);
                    free_hash_table(hash_table, mas_size);
                }

                if (mas_size > MAX_SIZE_OF_HASH_TABLE)
                {
                    cout << "Cannot make hash table with max compare number: " << max_comp << " and with size <= " << MAX_SIZE_OF_HASH_TABLE << endl;
                    break;
                }

                list_t *hash_table[mas_size];
                fill_hash_table(hash_table, mas_size, root, my_hash2);
                print_hash_table(hash_table, mas_size, my_hash2);

                int rez_hash = search_word_in_hash_table(hash_table, mas_size, word, my_hash2);
                if (rez_hash != -1)
                    cout << "\nHash for word '" << word << "' = " << rez_hash << endl;
                else
                    cout << "\nNo word '" << word << "' in hash table" << endl;

                free_hash_table(hash_table, mas_size);
            }
            else
            {
                cout << "Tree is empty" << endl;
            }
            break;
        }
        case 8:
        {
            _flushall();
            cout << "Enter the file name: ";
            string file_name;
            getline(cin, file_name);
            _flushall();
            cout << "Enter the word: ";
            string word;
            getline(cin, word);
            int rez = search_word_in_file(file_name, word);
            if (rez != -1 && rez != 0)
                cout << "Line in file '" << file_name << "' for word '" << word << "' = " << rez << endl;
            else if (rez == 0)
                cout << "No such word in file" << endl;
            else if (rez == -1)
                cout << "No such file" << endl;
            break;
        }
        case 9:
        {
            _flushall();
            cout << "Enter the file name: ";
            string file_name;
            getline(cin, file_name);
            _flushall();
            cout << "Enter the word: ";
            string word;
            getline(cin, word);

            int file_search_rez = -2;
            file_search_rez = search_word_in_file(file_name, word);
            if (file_search_rez == -1)
            {
                cout << "No such file" << endl;
                break;
            }
            if (file_search_rez == 0)
                cout << "Word is not found" << endl;

            int iterations_number = 10000;

            uint64_t time = 0;

            int file_avg_search_ticks = 0;

            for (int i = 0; i < iterations_number; i++)
            {
                time = tick();
                file_search_rez = search_word_in_file(file_name, word);
                time = tick() - time;
                file_avg_search_ticks += time;
            }
            file_avg_search_ticks /= iterations_number;
            printf("Search avg time for file: %d ticks; Last time: %llu\n", file_avg_search_ticks, time);

            tree_node *search_root = read_file(file_name);
            //balance_tree(&search_root);
            //print_tree(search_root);

            //tree_node **tree_search_rez = NULL;
            int comp_counter = 0;
            int tree_avg_search_ticks = 0;
            for (int i = 0; i < iterations_number; i++)
            {
                time = tick();
                //tree_search_rez = search_word_in_tree(&search_root, word, &comp_counter);
                search_word_in_tree(&search_root, word, &comp_counter);
                time = tick() - time;
                tree_avg_search_ticks += time;
                //printf("%d time: %d\n", i, time);
            }
            comp_counter /= iterations_number;
            tree_avg_search_ticks /= iterations_number;
            printf("Search avg time for tree: %d ticks; Last time: %llu\n", tree_avg_search_ticks, time);
            cout << "Compare number for tree: " << comp_counter << endl;


            balance_tree(&search_root);
            //delete_tree(&search_root);
            //search_root = read_file(file_name);
            //print_tree(search_root);

            //tree_node **balance_tree_search_rez = NULL;
            comp_counter = 0;
            int balance_tree_avg_search_ticks = 0;
            for (int i = 0; i < iterations_number; i++)
            {
                time = tick();
                //balance_tree_search_rez = search_word_in_tree(&search_root, word, &comp_counter);
                search_word_in_tree(&search_root, word, &comp_counter);
                time = tick() - time;
                balance_tree_avg_search_ticks += time;
                //printf("%d time: %d\n", i, time);
            }
            comp_counter /= iterations_number;
            balance_tree_avg_search_ticks /= iterations_number;
            printf("Search avg time for balanced tree: %d ticks; Last time: %llu\n", balance_tree_avg_search_ticks, time);
            cout << "Compare number for balanced tree: " << comp_counter << endl;

            int mas_size = count_nodes(root);
            mas_size = make_simple(mas_size);
            list_t *hash_table[mas_size];
            fill_hash_table(hash_table, mas_size, root, my_hash2);

            //int  hash_table_search_rez = -2;
            int hash_table_avg_search_ticks = 0;
            for (int i = 0; i < iterations_number; i++)
            {
                time = tick();
                //hash_table_search_rez = search_word_in_hash_table(hash_table, mas_size, word, my_hash2);
                search_word_in_hash_table(hash_table, mas_size, word, my_hash2);
                time = tick() - time;
                hash_table_avg_search_ticks += time;
            }
            hash_table_avg_search_ticks /= iterations_number;
            printf("Search avg time for hash table: %d ticks; Last time: %llu\n", hash_table_avg_search_ticks, time);

            free_hash_table(hash_table, mas_size);
            delete_tree(&search_root);

            break;
        }
        case 10:
        {
            _flushall();
            cout << "Enter the file name: ";
            string file_name;
            getline(cin, file_name);
            int file_size = get_file_size(file_name);
            if (file_size != -1)
            {
                cout << "File size: " << file_size << " bytes." << endl;
                tree_node *size_root = read_file(file_name);
                int nodes_number = count_nodes(size_root);
                int tree_size = nodes_number * sizeof (tree_node);
                //cout << "sizeif string: " << sizeof(string) << "; sizeof  tree_node*: " << sizeof(tree_node*) << endl;
                cout << "Tree size: " << tree_size << " bytes." << endl;
                int hash_table_size = nodes_number * sizeof (list_t) + sizeof(list_t**);
                cout << "Hash table size: " << hash_table_size << " bytes." << endl;
            }
            else
            {
                cout << "No such file" << endl;
            }
            break;
        }
        case 0:
        {
            cout << "Good buy!" << endl;
            break;
        }
        default:
            cout << "Wrong command" << endl;
            break;
        }
    }

    delete_tree(&root);
    return 0;
}
