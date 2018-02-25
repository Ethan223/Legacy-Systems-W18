/***************************
Name: Ethan Coles
ID: 0843081
Date: 11/03/2014
Assignment Name: Assignment 3
****************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "q1.h"

void pushNum(NumStack * ns, float value)
{
    if(ns->top >= MAX - 1)
    {
    	printf("Stack is full.\n");
    }
    else
    {
    	ns->top++;
        ns->numArr[ns->top] = value;
    }
}

float popNum(NumStack * ns)
{
    float value;

    if(ns->top < 0)
    {
    	printf("Stack is empty.\n");
    	return -1;
    }
    else
    {
        value = ns->numArr[ns->top];
        ns->top--;
        return value;
    }
}

void pushOp(OpStack * os, char opValue)
{
    if(os->top >= MAX - 1)
    {
        printf("Stack is full.\n");
    }
    else
    {
        os->top++;
        os->opArr[os->top] = opValue;
    }
}

int popOp(OpStack * os)
{
    char opValue;

    if(os->top < 0)
    {
        printf("Stack is empty.\n");
        return -1;
    }
    else
    {
        opValue = os->opArr[os->top];
        os->top--;
        return opValue;
    }
}

float operate(float x, float y, char operator)
{
    if(operator == '+') 
    {
        return (x+y);
    }
    else if(operator == '-') 
    {
        return (x-y);
    }
    else if(operator == '*')
    {
        return (x*y);
    }
    else if(operator == '/') 
    {
        if(y == 0) {
            printf("Cannot divide by 0.\n");
            return -1;
        }
        else
            return (x/y);
    }
    else 
    {
        printf("Could not operate.\n");
        return -1;
    }
}

bTree * createNode(char data[])
{
    bTree * newNode; 

    newNode = malloc(sizeof(bTree));
    strcpy(newNode->data, data);
    newNode->left = newNode->right = NULL;
    return newNode;
}

bTree * insertElement(bTree * root, bTree * node, char data[])
{
    if(node == NULL)
    {
        node = createNode(data);
        root = node;
    }

    else
    {
        node = createNode(data);

        if(root->left != NULL && root->right != NULL)
        {
            node->left = root;
            root = node;
        }

        else if(root->left != NULL)
        {
            root->right = node;
        }

        else
        {
            node->left = root;
            root = node;
        }
    }

    return root;
}