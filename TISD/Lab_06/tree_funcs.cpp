#include "structures.h"
#include "comporators.h"

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

tree_node **search_node(tree_node **root, string value)
{
    tree_node **rez = NULL;
    if (comp_string(&value, &((*root)->value)) < 0)
    {
        if ((*root)->left != NULL)
            rez = search_node(&((*root)->left), value);
    }
    else if (comp_string(&value, &((*root)->value)) > 0)
    {
        if ((*root)->right != NULL)
            rez = search_node(&((*root)->right), value);
    }
    else
    {
        return root;
    }

    return rez;
}

void print_tree(tree_node* root, int space)
{
    if (root == NULL)
        return;

    space += 5;

    print_tree(root->left, space);

    cout << endl;

    for (int i = 5; i < space; i++)
    {
        cout << " ";
    }
    cout << root->value << endl;

    print_tree(root->right, space);
}

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
