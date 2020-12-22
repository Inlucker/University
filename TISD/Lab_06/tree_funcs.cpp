#include "tree_funcs.h"
#include "structures.h"
#include "comporators.h"
#include "hash_funcs.h"

tree_node *create_node(string value)
{
    tree_node *new_node = new tree_node;
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

void add_node(tree_node *root, tree_node *node)
{
    //tree_node *tmp_root = *root;
    if (comp_string(&node->value, &root->value) < 0)
    {
        if (root->left != NULL)
            add_node(root->left, node);
        else
        {
            root->left = node;
        }
    }
    else
    {
        if (root->right != NULL)
            add_node(root->right, node);
        else
        {
            root->right = node;
        }
    }
}

tree_node **search_word_in_tree(tree_node **root, string word)
{
    tree_node **rez = NULL;
    if (comp_string(&word, &((*root)->value)) < 0)
    {
        if ((*root)->left != NULL)
            rez = search_word_in_tree(&((*root)->left), word);
    }
    else if (comp_string(&word, &((*root)->value)) > 0)
    {
        if ((*root)->right != NULL)
            rez = search_word_in_tree(&((*root)->right), word);
    }
    else
    {
        return root;
    }

    return rez;
}

void print_node_green(tree_node* root, int space, string word)
{
    if (root)
    {
        space += 5;

        print_node_green(root->left, space, word);

        //cout << endl;

        for (int i = 5; i < space; i++)
        {
            if (i % 5 == 4)
                cout << "|";
            else
                cout << " ";
        }
        if (root->value == word)
            cout << "\x1b[32m" << root->value << "\x1b[0m" << endl;
        //"\x1b[31mNo such word in tree\x1b[0m"
        else
            cout << root->value << endl;

        print_node_green(root->right, space, word);
    }
}

void print_searched_word_in_tree(tree_node* root, string word)
{
    if (root)
    {
        cout << endl;
        print_node_green(root, 0, word);
        cout << endl;
        int depth = 0;
        calculate_depth(root, &depth);
        cout << "Current depth = " << depth << endl;
    }
    else
    {
        cout << "Tree is empty" << endl;
    }
}

void print_node(tree_node* root, int space)
{
    if (root)
    {
        space += 5;

        print_node(root->left, space);

        //cout << endl;

        for (int i = 5; i < space; i++)
        {
            if (i % 5 == 4)
                cout << "|";
            else
                cout << " ";
        }
        cout << root->value << endl;

        print_node(root->right, space);
    }
}

void print_tree(tree_node* root)
{
    if (root)
    {
        cout << endl;
        print_node(root, 0);
        cout << endl;
        int depth = 0;
        calculate_depth(root, &depth);
        cout << "Current depth = " << depth << endl;
    }
    else
    {
        cout << "Tree is empty" << endl;
    }
}

int count_nodes(tree_node *root)
{
    int rez = 0;
    if (root)
    {
        rez += count_nodes(root->left);

        //cout << root->value << endl;
        rez++;

        rez += count_nodes(root->right);
    }
    return rez;
}

tree_node *find_node_by_id(tree_node *root, int id, int *cur_id)
{
    tree_node *rez = root;
    if (root)
    {
        rez = find_node_by_id(root->left, id, cur_id);
        if (*cur_id == id)
        {
            return rez;
        }

        //cout << *cur_id << ": " << root->value << endl;
        (*cur_id) += 1;
        if (*cur_id == id)
        {
            //cout << id << ": " << root->value << endl;
            return root;
        }

        rez = find_node_by_id(root->right, id, cur_id);
        if (*cur_id == id)
        {
            return rez;
        }
    }
    return rez;
}

tree_node *get_new_root(tree_node *root)
{
    int nodes_number = count_nodes(root);
    int id = nodes_number / 2;
    int cur_id = 0;
    tree_node *new_root = find_node_by_id(root, id, &cur_id);
    //cout << new_root << endl;
    return new_root;
}

void fill_root(tree_node *root, tree_node *tree, string root_value)
{
    //tree_node *rez = NULL;
    if (tree)
    {
        fill_root(root, tree->left, root_value);

        //cout << tree->value << endl;
        if (tree->value != root_value)
            add_node(root, create_node(tree->value));
        //add_node(root, tree);

        fill_root(root, tree->right, root_value);
    }
}

void balance_tree(tree_node **root)
{
    if (root && *root && ((*root)->left != NULL || (*root)->right) != NULL)
    {
        tree_node *tmp_root = get_new_root(*root);
        //cout << tmp_root << " points on: " << tmp_root->value << endl;
        tree_node *new_root = create_node(tmp_root->value);
        fill_root(new_root, *root, new_root->value);
        //cout << "NEW_ROOT:" << endl;
        //print_tree(new_root);

        delete_tree(root);

        *root = new_root;
        tree_node **left_new_root = &((*root)->left);
        balance_tree(left_new_root);
        tree_node **right_new_root = &((*root)->right);
        balance_tree(right_new_root);
    }
}

void calculate_depth(tree_node *root, int *cur_depth)
{
    if (root)
    {
        int rez1 = *cur_depth + 1;
        int rez2 = *cur_depth + 1;
        calculate_depth(root->left, &rez1);
        calculate_depth(root->right, &rez2);
        *cur_depth = max(rez1, rez2);
    }
}

/*void print_node_hash(tree_node *node, int m)
{
    if (node)
    {
        print_node_hash(node->left, m);

        int hash = my_hash(node->value, m);
        cout << hash << " " << node->value << endl;

        print_node_hash(node->right, m);
    }
}

void print_tree_hashes(tree_node *root)
{
    int mas_size = count_nodes(root);
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

    cout << endl;
    print_node_hash(root, mas_size);
    cout << endl;
}*/

void delete_tree(tree_node **root)
{
    if (root && *root)
    {
        tree_node *tmp_root = *root;
        if (tmp_root->left != NULL)
        {
            delete_tree(&(tmp_root->left));
        }
        if (tmp_root->right != NULL)
        {
            delete_tree(&(tmp_root->left));

        }
        tree_node *ptr_to_delete = *root;
        *root = NULL;
        delete ptr_to_delete;
    }
}
