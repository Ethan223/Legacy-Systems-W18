/***************************
Name: Ethan Coles
ID: 0843081
Date: 11/03/2014
Assignment Name: Assignment 3
****************************/
#define MAX 30

typedef struct bTree
{
	char data[MAX];
	struct bTree * left;
	struct bTree * right;
} bTree;

typedef struct NumStack
{
	float numArr[MAX];
	int top;
} NumStack;

typedef struct OpStack
{
	char opArr[MAX];
	int top;
} OpStack;

void printMenu();


float operate(float x, float y, char operator);

float popNum(NumStack * ns);

void pushNum(NumStack * ns, float value);

int popOp(OpStack * os);

void pushOp(OpStack * os, char opValue);


bTree * createNode(char data[]);

bTree * insertElement(bTree * root, bTree * node, char data[]);