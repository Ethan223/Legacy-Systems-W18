/***************************
Name: Ethan Coles
ID: 0843081
Date: 11/24/2014
Assignment Name: Assignment 4
****************************/
#define MAX 50

typedef struct AvlTree
{
	char key[MAX];
	int count;
	struct AvlTree * left;
	struct AvlTree * right;
	int height;
} AvlTree;

void printMenu();  /*Prints main menu*/

void inOrder(AvlTree *node);

void searchAboveFreq(AvlTree *node, int freq);

int search(AvlTree *node, char key[]);

int max(int x, int y);

int height(AvlTree * node);

int balFactor(AvlTree * node);

AvlTree * createNode(char key[]);

AvlTree * ll(AvlTree * currRoot);

AvlTree * rr(AvlTree * currRoot);

AvlTree * lr(AvlTree * currRoot);

AvlTree * rl(AvlTree * currRoot);

AvlTree * insert(AvlTree * head, AvlTree * newNode, int *sizePtr);

AvlTree * removeKey(AvlTree * head, char key[]);

AvlTree * getPredecessor(AvlTree * head);