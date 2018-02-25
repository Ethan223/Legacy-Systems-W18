/***************************
Name: Ethan Coles
ID: 0843081
Date: 11/24/2014
Assignment Name: Assignment 4
****************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avltree.h"

AvlTree * createNode(char key[])
{
	AvlTree * newNode;

	newNode = malloc(sizeof(AvlTree));
	strcpy(newNode->key, key);
	newNode->count = 1;  /*Assumes it does not already exist*/
	newNode->left = newNode->right = NULL;
	newNode->height = 1;

	return newNode;
}

int max(int x, int y)
{
	if(x > y)
		return x;
	else
		return y;
}

int height(AvlTree * node)
{
    if(node == NULL)
        return -1;
    else
        return node->height;
}

int balFactor(AvlTree * node)
{
    if(node == NULL)
        return 0;
    else
        return height(node->left) - height(node->right);
}

AvlTree * ll(AvlTree * currRoot)
{
    AvlTree * newRoot;
    AvlTree * temp;

    newRoot = currRoot->right;
    temp = newRoot->left;
    newRoot->left = currRoot;
    currRoot->right = temp;

    currRoot->height = max(height(currRoot->left), height(currRoot->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;

    return newRoot;
}

AvlTree * rr(AvlTree * currRoot)
{
    AvlTree * newRoot;
    AvlTree * temp;

    newRoot = currRoot->left;
    temp = newRoot->right;
    newRoot->right = currRoot;
    currRoot->left = temp;

    currRoot->height = max(height(currRoot->left), height(currRoot->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;

    return newRoot;
}

AvlTree * lr(AvlTree * currRoot)
{
    AvlTree * newRoot;
    
    currRoot->left = ll(currRoot->left);
    newRoot = rr(currRoot);

    return newRoot;
}

AvlTree * rl(AvlTree * currRoot)
{
    AvlTree * newRoot;
    
    currRoot->right = rr(currRoot->right);
    newRoot = ll(currRoot);

    return newRoot;
}

AvlTree * insert(AvlTree * node, AvlTree * newNode, int * sizePtr)
{
    if(node == NULL)
    {
        (*sizePtr)++;
        return newNode;
    }

    else if(strcmp(newNode->key, node->key) == 0)  /*Checks for matching key*/
    {
        node->count++; /*Does not insert*/
    }

    else if(strcmp(newNode->key, node->key) > 0)
    {
        node->right = insert(node->right, newNode, sizePtr);
    }

    else
    {
        node->left = insert(node->left, newNode, sizePtr);
    }


    node->height = max(height(node->left), height(node->right)) + 1;  /*Updates height*/

    if(balFactor(node) < -1)  /*Bf becomes -2*/
    {
        if(height(node->right->left) > height(node->right->right))
        {
            node = rl(node);
        }
        else
        {
            node = ll(node);
        }
    }

    else if(balFactor(node) > 1)  /*Bf becomes 2*/
    {
        if(height(node->left->right) > height(node->left->left))
        {
            node = lr(node);
        }
        else
        {
            node = rr(node);
        }
    }

    return node;
}

AvlTree * removeKey(AvlTree * head, char key[])
{
    if(head == NULL)
    {
        printf("no_such_key\n");
        return head;
    }

    else if(strcmp(key, head->key) > 0)  /*If greater, search goes right*/
    {
        head->right = removeKey(head->right, key);
    }

    else if(strcmp(key, head->key) < 0)  /*If smaller, search goes left*/
    {
        head->left = removeKey(head->left, key);
    }

    else if(strcmp(key, head->key) == 0)  /*If key is found*/
    {
        if(head->left == NULL && head->right == NULL)  /*Case I: Node has no children*/
        {
            AvlTree *toBeDeleted = head;
            
            if(head->count == 1) {
                head->count--;
                printf("key: %s, frequency: %d\n", head->key, head->count);
                head = NULL;
                free(toBeDeleted);
            }
            else {
                head->count--;
                printf("key: %s, frequency: %d\n", head->key, head->count);
            }   
        }
        else if(head->left == NULL && head->right != NULL)  /*Case II: Node has 1 child*/
        {
            AvlTree *toBeMoved = head->right;
            
            if(head->count == 1) {
                head->count--;
                printf("key: %s, frequency: %d\n", head->key, head->count);
                *head = *toBeMoved;
                free(toBeMoved);
            }
            else {
                head->count--;
                printf("key: %s, frequency: %d\n", head->key, head->count);
            }
        }
        else if(head->right == NULL && head->left != NULL)
        {
            AvlTree *toBeMoved = head->left;

            if(head->count == 1) {
                head->count--;
                printf("key: %s, frequency: %d\n", head->key, head->count);
                *head = *toBeMoved;
                free(toBeMoved);
            }
            else {
                head->count--;
                printf("key: %s, frequency: %d\n", head->key, head->count);
            }
        }
        else  /*Case III: Node has 2 children*/
        {
            AvlTree * predecessor = getPredecessor(head->right);

            if(head->count == 1) {
                head->count--;
                printf("key: %s, frequency: %d\n", head->key, head->count);
                strcpy(head->key, predecessor->key);
                head->count = predecessor->count;
                head->left = removeKey(head->left, predecessor->key);
            }
            else {
                head->count--;
                printf("key: %s, frequency: %d\n", head->key, head->count);
            }
        }
    }

    else
    {
        printf("no_such_key\n");
        return head;
    }


    if(head == NULL)
    {
        return head;
    }

    head->height = max(height(head->left), height(head->right)) + 1;  /*Updates height*/

    if(balFactor(head) < -1)  /*Bf becomes -2*/
    {
        if(height(head->right->left) > height(head->right->right))
        {
            head = rl(head);
        }
        else
        {
            head = ll(head);
        }
    }

    else if(balFactor(head) > 1)  /*Bf becomes 2*/
    {
        if(height(head->left->right) > height(head->left->left))
        {
            head = lr(head);
        }
        else
        {
            head = rr(head);
        }
    }
    
    return head;
}

AvlTree * getPredecessor(AvlTree * head)
{
    AvlTree *node = head;

    while(node->right != NULL)  /*Finds rightmost node of left subtree*/
    {
        node = node->right;
    }

    return node;
}

int search(AvlTree *node, char key[])
{
    int val;

    if(node != NULL && strcmp(node->key, key) == 0)
    {
        printf("key: %s, frequency: %d\n", node->key, node->count);
        val = 1;
    }
    else if(node != NULL)
    {
        val = 0;
        val = search(node->left, key);
        val = search(node->right, key);
    }
    return val;
}

void searchAboveFreq(AvlTree *node, int freq)
{
    if(node != NULL && node->count >= freq)
    {
        printf("key: %s, frequency: %d\n", node->key, node->count);
    }

    if(node != NULL) {
        searchAboveFreq(node->left, freq);
        searchAboveFreq(node->right, freq);
    }
}

void inOrder(AvlTree *node)
{
    if(node != NULL) {
        inOrder(node->left);
        printf("%s", node->key);
        inOrder(node->right);
    }
}