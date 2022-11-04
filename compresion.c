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
    struct node *left, *right, *father;
};

struct node *new_node(int uses, char char_element, struct node *father)
{
    printf("boing1.2");
    struct node *temp = (struct node *)malloc(sizeof(struct node)); // Allocating memory to the node
    temp->data_element = 1;
    temp->uses = uses;
    temp->char_element = char_element;
    temp->left = temp->right = NULL;
    temp->father = father;
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

void insert(struct node *, struct node *);
void insert(struct node *father, struct node *node) // Function to insert a new node
{
    if (father->char_element != 0)
        return;
    if (!father->left)
    {
        father->left = new_node(node->uses, 0, father);
        father->left->right = node;
    }
    else
    {
        insert(father->left, node);
        insert(father->right, node);
    }
}

int main()
{
    FILE *fp;
    fp = fopen("Hola.txt", "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return (-1);
    }
    if (fgets(input, MAX, fp) != NULL)
    {
        /* writing content to stdout */
        puts(input);
    }
    fclose(fp);

    return (0);
}