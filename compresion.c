#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024
char input[MAX];

struct node
{
    int data_element;
    int uses;
    char char_element;
    struct node *left, *right, *parent;
};

void insert(struct node *, struct node *);
void exchange(struct node *, struct node *);
void ParentValue(struct node *);
struct node *compareParents(struct node *, struct node *);
int compare(struct node *);

struct node *new_node(int uses, char char_element)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node)); // Allocating memory to the node
    temp->data_element = 1;
    temp->uses = uses;
    temp->char_element = char_element;
    temp->left = temp->right = temp->parent = NULL;
    return temp;
}

void display(struct node *root) // A function for the inroder traversal of the binary tree
{
    if (root != NULL)
    {
        display(root->left);
        printf("%c \n", root->char_element);
        display(root->right);
    }
}

void insert(struct node *parent, struct node *node) // Function to insert a new node
{
    if (parent->char_element != 0)
        return;
    if (!parent->right)
    {
        parent->left = new_node(node->uses, 0);
        parent->left->parent = parent;
        parent->right = node;
        node->parent = parent;
    }
    else
    {
        insert(parent->left, node);
        insert(parent->right, node);
    }
}

void exchange(struct node *node, struct node *objective)
{
    struct node *temp = node->parent;
    node->parent = objective->parent;
    objective->parent = temp;
    node->parent->right = node;
    objective->parent->left = objective;
}

void ParentValue(struct node *parent)
{
    int Lchild = parent->left->uses;
    int Rchild = parent->right->uses;
    parent->uses = Lchild + Rchild;
}

struct node *compareParents(struct node *node, struct node *parent)
{
    if (node->uses > parent->parent->right->uses)
    {
        return parent;
    }
    return NULL;
}

int compare(struct node *node)
{
    int nodeValue = node->uses;
    int ciclo = 1;
    struct node *temp = NULL;
    struct node *ex = NULL;
    if (node->parent->left->uses == node->parent->right->uses)
    {
        // cuando son iguales no pasa nada
    }
    if (node->uses > node->parent->left->uses)
    {
        while (ciclo == 1)
        {
            temp = compareParents(node, node->parent); // metodo de comparar con el hermano del padre
            if (temp)
            {
                ex = temp;
            }
        }
        if (ex)
        {
            exchange(node->parent, ex);
        }
    }
}

int main()
{
    fgets(input, MAX, stdin);
    char letters[107];
    struct node *nodes[107];
    size_t let = 0;
    int new;
    struct node *root = new_node(0, 0);
    for (size_t i = 0; i < strlen(input) - 1; i++)
    {
        new = 1;
        for (size_t j = 0; j < strlen(letters); j++)
        {
            if (input[i] == letters[j])
            {
                new = 0;
                // aqui es repetido
                break;
            }
        }
        if (new) // Nuevo character, nuevo nodo
        {
            letters[let++] = input[i];
            nodes[i] = new_node(1, input[i]);
            insert(root, nodes[i]);
        }
    }
    display(root); // Function to display the binary tree elements

    return 0;
}