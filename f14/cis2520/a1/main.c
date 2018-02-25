/***************************
Name: Ethan Coles
ID: 0843081
Date: 09/29/2014
Assignment Name: Assignment 1
****************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void carbon();    /*This function print all possible combinations of the 6-letter word "carbon"*/
int ackermann();    /*Function gives values of Ackermann's function using recursion*/
double newton();    /*Function calculates square root of a real number using Newton's Method with and without recursion.*/

int main(int argc, char *argv[])
{
    if(argc == 2 && strcmp(argv[1], "carbon") == 0)
    {
        printf("QUESTION 1:\n");
        carbon();
        printf("\n");
    }
    
    else if(argc == 2 && strcmp(argv[1], "ackermann") == 0)
    {
        printf("QUESTION 2:\n");
        ackermann();
        printf("\n");
    }
    
    else if(argc == 2 && strcmp(argv[1], "newton") == 0)   
    {    
        printf("QUESTION 3:\n");
        newton();
        printf("\n");
    }

    else
    {
        printf("Usage: ./a1 programName\n");
    }

	return 0;
}