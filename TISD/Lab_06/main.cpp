#include "defines.h"
#include "structures.h"
#include "io_funcs.h"
#include "tree_funcs.h"
#include "list_funcs.h"
#include "hash_funcs.h"

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
            tree_node **node = search_word_in_tree(&root, word);
            if (node)
            {
                cout << "Word '" << (*node)->value << "' in tree have left " << (*node)->left << " ptr and right " << (*node)->right << " ptr." << endl;
                if ((*node)->left)
                    cout << "Left word: " << (*node)->left->value << endl;
                if ((*node)->right)
                    cout << "Right word: " << (*node)->right->value << endl;
                print_searched_word_in_tree(root, word);
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
            tree_node **node = search_word_in_tree(&root, word);
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
