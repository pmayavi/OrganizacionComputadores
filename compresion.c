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
int compare(struct node *);
struct node *find(struct node *, char c);
void print_nodes(struct node *, char *, int);

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
        ParentValue(parent);
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
    int Lchild = 0;
    if (parent->left)
        Lchild = parent->left->uses;
    int Rchild = parent->right->uses;
    parent->uses = Lchild + Rchild;
}

int compare(struct node *node)
{
    struct node *temp = node;
    struct node *ex = NULL;
    if (node->uses > node->parent->right->uses)
    {
        while (!temp || temp->parent)
        {
            temp = temp->parent;
            if (node->uses > temp->right->uses)
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

struct node *find(struct node *node, char c)
{
    if (!node)
        return NULL;
    if (node->char_element == c)
        return node;
    if (node->char_element != 0)
        return NULL;
    struct node *f = find(node->left, c);
    if (f)
        return f;
    return find(node->right, c);
}

void print_nodes(struct node *node, char binary[], int position)
{

    if (node->char_element)
    {
        if (node->parent->left->char_element)
        {
            binary[position] = '1';
            position++;
        }
        if (node->parent->right->char_element)
        {
            binary[position] = '0';
            position++;
        }
        printf("[%c,%d,%s]\n", node->char_element, node->uses, binary);
    }
    else
    {
        if (node->parent->left->char_element)
        {
            binary[position] = '1';
            position++;
        }
        if (node->parent->right->char_element)
        {
            binary[position] = '0';
            position++;
        }
    }
    print_nodes(node->left, binary, position);
    print_nodes(node->right, binary, position);
}

int main()
{
    fgets(input, MAX, stdin);
    char letters[107];
    size_t let = 0;
    int new;
    struct node *root = new_node(0, 0);
    struct node *temp;
    for (size_t i = 0; i < strlen(input) - 1; i++)
    {
        new = 1;
        for (size_t j = 0; j < strlen(letters); j++)
        {
            if (input[i] == letters[j])
            {
                new = 0;
                // aqui es repetido
                temp = find(root, letters[j]);
                printf("%d\n", temp->uses);
                temp->uses += 1;
                ParentValue(temp->parent);
                compare(temp);
                break;
            }
        }
        if (new) // Nuevo character, nuevo nodo
        {
            letters[let++] = input[i];
            insert(root, new_node(1, input[i]));
        }
    }
    char binary[10];
    print_nodes(root, binary, 0); // Function to display the binary tree elements

    return 0;
}