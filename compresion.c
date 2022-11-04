#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024
#define N 107
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
void print_nodes(struct node *);
int data = N;

struct node *new_node(int uses, char char_element)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node)); // Allocating memory to the node
    temp->data_element = data--;
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
    objective->parent->left = node;

    objective->parent = temp;
    objective->parent->left = objective;
    return;
    ParentValue(objective->parent);
    ParentValue(node);
}

void ParentValue(struct node *node)
{
    int Lchild = 0;
    if (node->left)
        Lchild = node->left->uses;
    int Rchild = node->right->uses;
    node->uses = Lchild + Rchild;
    if (node->parent)
        ParentValue(node->parent);
}

int compare(struct node *node)
{
    struct node *temp = node->parent;
    struct node *ex = NULL;
    if (temp->parent && node->uses > temp->parent->right->uses)
    {
        do
        {
            temp = temp->parent;
            printf("%d > %d\n", node->uses, temp->right->uses);
            if (node->uses > temp->right->uses)
                ex = temp;
        } while (temp->parent);
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

void print_nodes(struct node *node)
{
    // if (node->char_element)
    printf("[%c,%d", node->char_element, node->uses);
    if (node->right)
        printf("%c]", node->right->char_element);
    if (node->left)
        printf("%c]\n", node->left->char_element);
    if (node->right)
        print_nodes(node->right);
    if (node->left)
        print_nodes(node->left);
}

int main()
{
    fgets(input, MAX, stdin);
    char letters[N];
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
    print_nodes(root); // Function to display the binary tree elements

    return 0;
}