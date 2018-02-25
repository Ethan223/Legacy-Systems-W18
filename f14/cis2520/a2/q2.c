/***************************
Name: Ethan Coles
ID: 0843081
Date: 10/14/2014
Assignment Name: Assignment 2
****************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXSIZE 30

typedef struct Stack
{
	int * stackArr;
	int top;
} Stack;

void push(Stack * s, int value);

int pop(Stack * s);

int operate(int x, int y, char element);

int main(int argc, char *argv[])
{
    Stack * s;
    char element;
    int i = 0;

    int x;
    int y;
    int ans;

    if(argc != 2)
    {
    	printf("Usage: ./q2 <equation>\n");
    	return -1;
    }

    s = malloc(sizeof(Stack));
    s->stackArr = malloc(sizeof(int)*MAXSIZE);
    s->top = -1;

    while(i < strlen(argv[1]))
    {
        element = argv[1][i];

        if(isdigit(element))
        {
        	push(s, element-'0');
        }

        else
        {
            y = pop(s);
            x = pop(s);
            ans = operate(x, y, element);
            push(s, ans);
        }


        i++;
    }
    
    printf("Answer: %d\n", ans);
    free(s->stackArr);
    free(s);

	return 0;
}

void push(Stack * s, int value)
{
    if(s->top >= MAXSIZE - 1)
    {
    	printf("Stack is full.\n");
    }
    else
    {
    	s->top++;
        s->stackArr[s->top] = value;
    }
}

int pop(Stack * s)
{
    int value;

    if(s->top < 0)
    {
    	printf("Stack is empty.\n");
    	return -1;
    }
    else
    {
        value = s->stackArr[s->top];
        s->top--;
        return value;
    }
}

int operate(int x, int y, char element)
{
    if(element == '+') 
    {
    	return (x+y);
    }
    else if(element == '-') 
    {
    	return (x-y);
    }
    else if(element == '*')
    {
        return (x*y);
    }
    else if(element == '/') 
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