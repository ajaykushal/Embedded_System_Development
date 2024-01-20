/*******************************************************************************************
 * File Name: Lab3.c
 *
 * Objectives:
 * - To implement a binary search tree
 *
 * Student Name:   Ajay Kumar
 * Student Number: 8831954
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char key[10];   // A string representing a key
    int data;       // Data associated with the key
} data_t;

// Structure defining a binary tree node. Lower sorted values will go to the left, higher to the right.
typedef struct node 
{
    data_t data;    // Contains data and a key
    struct node* left;
    struct node* right;
} node_t;

// Data to be stored in tree.
data_t inputData[] = 
{
    {"blue", 85},
    {"red", 77},
    {"yellow", -4},
    {"white", 152},
    {"black", 0},
    {"green", -33},
    {"orange", 275},
    {"purple", 654},
    {"brown", 99},
    {"grey", -5}
};

void binarySearchTree_AddNode(node_t** ppRoot, data_t* pData);
void binarySearchTree_PrintTreeInOrder(node_t* pRoot);
void binarySearchTree_DeleteTree(node_t** ppNode);

int main()
{

    node_t* pRoot = NULL;   // Pointer to root of the binary tree
    // Insert all the data into the binary tree
    int i;
    for (i = 0; i < (sizeof(inputData) / sizeof(inputData[0])); i++)
    {
        binarySearchTree_AddNode(&pRoot, &inputData[i]);
    }

    // Print the entire tree.
    binarySearchTree_PrintTreeInOrder(pRoot);

    // Delete the tree
    binarySearchTree_DeleteTree(&pRoot);

    return 0;
}

/**
* Brief: This function adds a new node to the binary search tree
* Inputs:
*       ppRoot - Pointer to the root's reference
*       pData - Pointer to data to be added
*/
void binarySearchTree_AddNode(node_t** ppRoot, data_t* pData) 
{
    node_t* pCurrent = *ppRoot;
    node_t* pParent = NULL;
    int nComparison = 0;

    // Find the insertion point
    while (pCurrent != NULL) 
    {
        nComparison = strcmp(pData->key, pCurrent->data.key);
        if (nComparison < 0) 
        {
            pParent = pCurrent;
            pCurrent = pCurrent->left;
        }
        else if (nComparison > 0) 
        {
            pParent = pCurrent;
            pCurrent = pCurrent->right;
        }
        else 
        {
            // If the key is the same as the node's key, update the node's data
            pCurrent->data = *pData;
            return;
        }
    }

    // Create a new node and add it to the tree
    node_t* pNode = (node_t*)malloc(sizeof(node_t));

    if (pNode == NULL)
    {
        fprintf(stderr, "Could not allocate memory, Memory full!\n");
        exit(EXIT_FAILURE);
    }

    pNode->data = *pData;
    pNode->left = NULL;
    pNode->right = NULL;

    if (pParent == NULL) 
    {
        *ppRoot = pNode;
    }
    else if (strcmp(pData->key, pParent->data.key) < 0) 
    {
        pParent->left = pNode;
    }
    else 
    {
        pParent->right = pNode;
    }
}

/**
* Brief: This function prints all the contents of the binary search tree in the ascending order (smaller to greater).
* Inputs:
*       pRoot - Pointer to the root
*/

void binarySearchTree_PrintTreeInOrder(node_t* pRoot)
{
    if (pRoot == NULL) 
    {
        // tree is empty, nothing to print
        printf("Tree is empty.\n");
        return;
    }

    node_t* stack[100] = { NULL };    // stack to store the nodes
    int top = -1;           // initialize the top of the stack

    // loop through the tree until it is empty
    while (pRoot != NULL || top != -1)
    {
        // traverse the left subtree and push nodes onto stack
        while (pRoot != NULL)
        {
            // check if stack is full
            if (top == 99) 
            {
                printf("Stack overflow error.\n");
                return;
            }
            stack[++top] = pRoot;
            pRoot = pRoot->left;
        }

        // pop the node from the stack and print its data
        pRoot = stack[top--];
        printf("Key: %s, Data: %d\n", pRoot->data.key, pRoot->data.data);

        // traverse the right subtree
        pRoot = pRoot->right;
    }
}


/**
* Brief: This function deletes all the nodes in the binary search tree
* Inputs:
*       ppRoot - Pointer to the root's reference
*/
void binarySearchTree_DeleteTree(node_t** ppNode) 
{
    // Check if the root pointer is NULL
    if (ppNode == NULL || *ppNode == NULL) 
    {
        printf("Error: Tree is already empty\n");
        return;
    }

    // Create a stack to maintain nodes to be deleted
    node_t* stack[100] = { NULL };
    int top = -1;

    // Push the root node onto the stack
    stack[++top] = *ppNode;

    // Loop until the stack is empty
    while (top >= 0) 
    {
        // Pop the top node from the stack
        node_t* curr = stack[top--];

        // Push the right child onto the stack (if not NULL)
        if (curr->right != NULL) 
        {
            stack[++top] = curr->right;
        }

        // Push the left child onto the stack (if not NULL)
        if (curr->left != NULL) 
        {
            stack[++top] = curr->left;
        }

        // Delete the current node
        free(curr);
    }

    // Set the root pointer to NULL
    *ppNode = NULL;

    printf("\n\nTree deleted successfully\n");
}
