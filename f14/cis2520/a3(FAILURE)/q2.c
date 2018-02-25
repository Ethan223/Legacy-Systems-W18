/***************************
Name: Ethan Coles
ID: 0843081
Date: 11/03/2014
Assignment Name: Assignment 3
****************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Heap
{
	int array[20][10];
} Heap;

/*Heap * createNode(int key, char * content);*/

Heap * insertElement(Heap * node, int i);

int main(int argc, char *argv[])
{
    Heap * tree;
    FILE * data;
    char buffer[101];

    if(argc != 2)
    {
    	printf("Usage: ./q2 <fileName>\n");
    	return -1;
    }

    data = fopen(argv[1], "r");
    if (data == NULL)
    {
        printf("Error opening file.\n");
        return -1;
    }

    tree = malloc(sizeof(Heap));

    fgets(buffer, 101, data);
    while(!feof(data))
    {
        int i = 0;
        int j = 0;
        
        tree->array[i][j] = atoi(strtok(buffer, " "));
        for(j=1; j<10; i++)
        {
        	tree->array[i][j] = atoi(strtok(NULL, " "));
        }

        tree = insertElement(tree, i);

        fgets(buffer, 101, data);
        i++;
    }

    free(tree);
	return 0;
}

/*Heap * createNode(int key, char * content)
{
	Heap * newNode;

	newNode = malloc(sizeof(Heap));
	newNode->array;


	return newNode;
}*/

Heap * insertElement(Heap * node, int i)
{
	/*int key;

    key = node->array[i][0] + node->array[i][1] + node->array[i][2];*/
	/*if(node == NULL)
	{
        node = createNode(key, content);
	}*/

	/*else if(key <= node->key)
	{
		node->left = insertElement(node->left);
	}

	else
	{
		node->right = insertElement(node->right);
	}*/

	return node;
}