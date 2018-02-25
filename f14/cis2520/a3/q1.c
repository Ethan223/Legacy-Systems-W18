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

int main(int argc, char *argv[])
{
    int i = 0;
    char element;
    bTree * root = NULL;
    bTree * newPtr = NULL;
    NumStack * ns;
    OpStack * os;
    char buffer[MAX];

    float x;
    float y;
    char operator;
    float ans;

    char choice[MAX];

    ns = malloc(sizeof(NumStack));
    os = malloc(sizeof(OpStack));

    if(argc != 2)
    {
    	printf("Usage: ./q2 <equation>\n");
    	return -1;
    }

    while(i < strlen(argv[1]))
    {
        element = argv[1][i];

        if(element != '+' && element != '-' && element != '*' && element != '/' && element != '(' && element != ')')
        {
            if(argv[1][i+1] == '.')
            {
                float tenth;
                float hundredth;
                float sum;

                tenth = (argv[1][i+2] - '0') * 0.1;
                hundredth = (argv[1][i+3] - '0') * 0.01;
                sum = (element - '0') + tenth + hundredth;
                pushNum(ns, sum);
                
                sprintf(buffer, "%.2f", sum);
                
                i += 3;   /*Moves over the decimal places that were parsed*/
            }

            else {
                pushNum(ns, element - '0'); /*Subtracting '0' gives the correct integer value from ascii value*/
                sprintf(buffer, "%c", element-'0');
            }

            root = insertElement(root, newPtr, buffer);

        }

        else if(element == '+' || element == '-' || element == '*' || element == '/' || element == '(')
        {
            pushOp(os, element);
            sprintf(buffer, "%c", element);
            root = insertElement(root, newPtr, buffer);
        }

        else if (element == ')')
        {
            y = popNum(ns);
            x = popNum(ns);
            operator = popOp(os);
            popOp(os); /*Gets rid of opening bracket*/

            ans = operate(x, y, operator);
            pushNum(ns, ans);
        }

        i++;
    }

    do
    {
        printMenu();
        fgets(choice, MAX, stdin);

        if(choice[0] == '1' && choice[1] == '\n')
        {

        }

        else if(choice[0] == '2' && choice[1] == '\n')
        {

        }

        else if(choice[0] == '3' && choice[1] == '\n')
        {

        }

        else if(choice[0] == '4' && choice[1] == '\n')
        {

        }

        else if(choice[0] == '5' && choice[1] == '\n')
        {

        }

        else if(choice[0] == '6' && choice[1] == '\n')
        {
            printf("Result: %.2f\n", ans);
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

	free(ns);
    free(os);
    return 0;
}

void printMenu()
{
	printf("\n**********************\n");
	printf("*     MAIN MENU      *\n");
	printf("**********************\n");
	printf("1)Display\n");
	printf("2)Preorder\n");
	printf("3)Inorder\n");
	printf("4)Postorder\n");
	printf("5)Update\n");
	printf("6)Calculate\n");
	printf("7)Exit\n");
	printf("> ");
}