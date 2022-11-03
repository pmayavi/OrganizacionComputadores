#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node
{
    int data_element;
    char char_element;
    struct node *left, *right;
};

struct node *new_node(char char_element)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node)); // Allocating memory to the node
    temp->data_element = 1;
    temp->char_element = char_element;
    temp->left = temp->right = NULL;
    return temp;
}

void display(struct node *root) // A function for the inroder traversal of the binary tree
{
    if (root != NULL)
    {
        display(root->left);
        printf("%d \n", root->data_element);
        display(root->right);
    }
}

struct node *insert(struct node *node, int data_element) // Function to insert a new node
{

    if (node == NULL)
        return new_node(data_element); // Return a new node if the tree if empty
    if (data_element < node->data_element)
    {
        node->left = insert(node->left, data_element);
    }
    else if (data_element > node->data_element)
    {
        node->right = insert(node->right, data_element);
    }
    return node;
}

int main()
{
    char input[1024];
    char letters[107];
    int use[107];
    gets(input);
    int new;
    for (size_t i = 0; i < strlen(input); i++)
    {
        new = 1;
        for (size_t j = 0; j < strlen(letters); j++)
        {
            if (input[i] == letters[j])
            {
                new = 0;
                use[j] += 1;
                break;
            }
        }
        if (new)
    }

    struct node *root = NULL;
    root = insert(root, 10);
    insert(root, 20);
    insert(root, 30);
    insert(root, 40);
    insert(root, 50);
    insert(root, 60);
    insert(root, 70);

    display(root); // Function to display the binary tree elements

    return 0;
}