#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node
{
    int data_element;//el valor de la izquierda del pdf
    int uses;
    char char_element;
    struct node *left, *right, *father;
};

struct node *new_node(int uses, char char_element, struct node *father)
{
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

return void ParentValue (struct node parent){
    int Lchild= parent->left->uses;
    int Rchlid= parent->right->uses;
    parent->uses=Lchild+Rchild;
}

int compare (struct node node) {
    nodeValue = node->uses;
    int ciclo = 1;
    temp=NULL;
    exchange=NULL;
    if (node->parent->left->uses== node->parent->right->uses){
        //cuando son iguales no pasa nada
    }
    if (node->uses > node->parent->left){
        while (ciclo == 1){
            temp= compareParents(node, node->parent);//metodo de comparar con el hermano del padre
            if (temp){
                exchange=temp;
            }
        }
        if(exchange){
            exchange(node->parent,exchange);
        }
    }
}

int compareParents (struct node node, struct node parent){
    if (node->value > parent->parent->right){
        return parent;
    }
    return NULL;
}

void exchange (struct node,struct objective){
    temp=node->parent
    node->parent=objective->parent;
    objective->parent=temp;
    node->parent->right=node;
    objective->parent->left=objective;
}

int main()
{
    char input[1024];
    char letters[107];
    size_t let = 0;
    int use[107];
    gets(input);
    int new;
    struct node *root = NULL;
    root = insert(root, 10);
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
        {
        }
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