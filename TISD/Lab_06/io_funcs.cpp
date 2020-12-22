#include "io_funcs.h"
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

int search_word_in_file(string file_name, string word)
{
    ifstream f(file_name);
    int n = -1;
    bool flag = false;
    if (f.is_open())
    {
        string input = "";
        n = 0;
        while(getline(f, input))
        {
            n++;
            if (input == word)
            {
                flag = true;
                break;
            }
        }
        if (!flag)
            n = 0;
    }
    return n;
}
