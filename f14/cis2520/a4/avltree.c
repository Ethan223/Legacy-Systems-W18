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

int main(int argc, char *argv[])
{
    char choice[MAX];
    char fileName[MAX];
    char keyInput[MAX];
    char buffer[MAX+450];
    FILE * data;

    AvlTree *head = NULL;
    AvlTree *newNode;
    int size = 0;
    int *sizePtr = &size;
    int found = 0;
    char freq[MAX];

    do {
    	printMenu();
        fgets(choice, MAX, stdin);

        if(choice[0] == '1' && choice[1] == '\n')
        {
            do {
                printf("filename: ");
                fgets(fileName, MAX, stdin);
                strtok(fileName, "\n");  /*Removes trailing \n*/
                data = fopen(fileName, "r");

                if(data == NULL) {
                    printf("Error opening file.  Try again.\n");
                }
            } while(data == NULL);

            while(!feof(data))
            {
                fscanf(data, "%s", buffer);
                newNode = createNode(buffer);
                head = insert(head, newNode, sizePtr);
            }
            fclose(data);
            printf("Initialized!\n");
        }

        else if(choice[0] == '2' && choice[1] == '\n')
        {
            printf("find key: ");
            fgets(keyInput, MAX, stdin);
            strtok(keyInput, "\n");
            found = search(head, keyInput);

            if(found == 0)
                printf("no_such_key\n");
        }

        else if(choice[0] == '3' && choice[1] == '\n')
        {
            printf("insert key: ");
            fgets(keyInput, MAX, stdin);
            strtok(keyInput, "\n");
            newNode = createNode(keyInput);
            head = insert(head, newNode, sizePtr);
            search(head, keyInput);
        }

        else if(choice[0] == '4' && choice[1] == '\n')
        {
            printf("remove key: ");
            fgets(keyInput, MAX, stdin);
            strtok(keyInput, "\n");
            head = removeKey(head, keyInput);
        }

        else if(choice[0] == '5' && choice[1] == '\n')
        {
            if(head == NULL) {
                printf("height: 0, size: 0\n");
            }
            else {
                printf("height: %d, size: %d\n", head->height, size);  /*Display height and size(# of nodes) of tree*/
            }
        }

        else if(choice[0] == '6' && choice[1] == '\n')
        {
            printf("frequency: ");
            fgets(freq, MAX, stdin);
            searchAboveFreq(head, atoi(freq));
        }

        else if(choice[0] == '7' && choice[1] == '\n')
        {
            break;
        }

        else
        {
            printf("Invalid option.\n");
        }
    } while(!(choice[0] == '7' && choice[1] == '\n'));
	
	return 0;
}

void printMenu()
{
	printf("\n**********************\n");
	printf("*-----MAIN MENU------*\n");
    printf("* Ethan Coles        *\n");
    printf("* 0843081            *\n");
	printf("**********************\n");
	printf("1)Initialization\n");
	printf("2)Find\n");
	printf("3)Insert\n");
	printf("4)Remove\n");
	printf("5)Check Height and Size\n");
	printf("6)Find All(above a given frequency)\n");
	printf("7)Exit\n");
	printf("avl/> ");
}