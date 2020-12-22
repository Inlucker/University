#include "io_funcs.h"
#include "tree_funcs.h"
#include "structures.h"

tree_node *read_file(string file_name)
{
    tree_node *root = NULL;
    ifstream f(file_name);
    if (f.is_open())
    {
        string input = "";
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

int get_file_size(string file_name)
{
    int size = -1;
    ifstream file(file_name);
    if (file.is_open())
        {
            size = 0;
            file.seekg (0, std::ios::end);
            size = file.tellg();
            file.close();
        }
    return size;
}
