/***************************
Name: Ethan Coles
ID: 0843081
Date: 10/14/2014
Assignment Name: Assignment 2
****************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "q1.h"

ToRent * addToRent(ToRent * head, ToRent * newCar)
{
    ToRent * node;

    node = head;

    if(head == NULL)
    {
        head = newCar;
    }

    else if(newCar->mileage <= node->mileage)    /*Adds to front*/
    {
        newCar->next = node;
        head = newCar;
    }

    else    /*Adds to middle and end*/
    {
        while(node->next != NULL)
        {
            if(newCar->mileage <= node->next->mileage)
            {
                break;    
            }

            node = node->next;
        }

        newCar->next = node->next;    /*node-> is NULL when at back, therefore next new pointer will point to NULL*/
        node->next = newCar;
    }
    
    return head;
}

Rented * addRented(ToRent * toRentHead, Rented * rentedHead, char * returnDate)
{
    Rented * temp;
    Rented * node;

    /*Creates new record of Rented*/
    temp = malloc(sizeof(Rented));
    temp->plateNum = malloc(sizeof(char)*MAX_SIZE);

    strcpy(temp->plateNum, toRentHead->plateNum);
    temp->mileage = toRentHead->mileage;
    temp->returnDate = atoi(returnDate);
    temp->next = NULL;

    toRentHead = toRentHead->next;

    /*Adds record to Rented list*/
    node = rentedHead;

    if(rentedHead == NULL)
    {
        rentedHead = temp;
    }

    else if(temp->returnDate <= node->returnDate)
    {
        temp->next = node;
        rentedHead = temp;
    }

    else
    {
        while(node->next != NULL)
        {
            if(temp->returnDate <= node->next->returnDate)
            {
                break;    
            }

            node = node->next;
        }

        temp->next = node->next;
        node->next = temp;
    }

    return rentedHead;
}

InRepair * addRepair(InRepair * head, InRepair * returnedCar)
{
    InRepair * node;

    node = head;

    if(head == NULL)
    {
        head = returnedCar;
    }

    else
    {
    	returnedCar->next = node;
        head = returnedCar;
    }

    return head;
}

ToRent * createCar(char * plateNum, int mileage)
{
	ToRent * temp;

    temp = malloc(sizeof(ToRent));
    temp->plateNum = malloc(sizeof(char)*MAX_SIZE);

    strcpy(temp->plateNum, plateNum);
    temp->mileage = mileage;
    temp->next = NULL;

    return temp;
}

InRepair * createRepairRecord(char * plateNum, int mileage)
{
    InRepair * temp;

    temp = malloc(sizeof(InRepair));
    temp->plateNum = malloc(sizeof(char)*MAX_SIZE);

    strcpy(temp->plateNum, plateNum);
    temp->mileage = mileage;
    temp->next = NULL;

    return temp;
}

ToRent * returnToRent(ToRent * toRentHead, Rented * rentedHead, char * plateNum, int mileage)
{
    Rented * node;
    ToRent * returnedCar;
    node = rentedHead;
    int found = 0;

    if(strstr(plateNum, node->plateNum) != NULL)
    {
        returnedCar = createCar(plateNum, mileage + node->mileage);
        toRentHead = addToRent(toRentHead, returnedCar);
    }

    else
    {
        while(node->next != NULL)
        {
            if(strstr(plateNum, node->next->plateNum) != NULL)
            {
                break;
                found = 1;    
            }

            node = node->next;
        }

        if(found == 1)
        {
            returnedCar = createCar(plateNum, mileage + node->next->mileage);
            toRentHead = addToRent(toRentHead, returnedCar);
        }
        else {
            return toRentHead;
        }
    }
    return toRentHead;
}

Rented * removeRented(Rented * rentedHead, char * plateNum)
{
    Rented * node;
    Rented * temp;
    int found = 0;

    node = rentedHead;

    if(strstr(plateNum, node->plateNum) != NULL)
    {
        temp = node;
        node = node->next;
        free(temp);
        printf("Successfully returned.\n");
    }

    else
    {
        while(node->next != NULL)
        {
            if(strstr(plateNum, node->next->plateNum) != NULL)
            {
                break;
                found = 1;    
            }

            node = node->next;
        }

        if(found == 1)
        {
            temp = node->next;    /*Deletes in middle of list*/
            node->next = node->next->next;
            free(temp);
            printf("Successfully returned.\n");
        }
        else {
            printf("Car with that plate number was not found in our records.\n");
        }
    }

    return rentedHead;
}

InRepair * returnToRepair(InRepair * inRepairHead, Rented * rentedHead, char * plateNum, int mileage)
{
	Rented * node;
    InRepair * returnedCar;
    node = rentedHead;
    int found = 0;

    if(strstr(plateNum, node->plateNum) != NULL)
    {
        returnedCar = createRepairRecord(plateNum, mileage + node->mileage);
        inRepairHead = addRepair(inRepairHead, returnedCar);
    }

    else
    {
        while(node->next != NULL)
        {
            if(strstr(plateNum, node->next->plateNum) != NULL)
            {
                break;
                found = 1;    
            }

            node = node->next;
        }

        if(found == 1)
        {
            returnedCar = createRepairRecord(plateNum, mileage + node->next->mileage);
            inRepairHead = addRepair(inRepairHead, returnedCar);
        }
        else {
            return inRepairHead;
        }
    }
    return inRepairHead;
}

InRepair * removeInRepair(InRepair * inRepairHead, char * plateNum)
{
	InRepair * node;
    InRepair * temp;
    int found = 0;

    node = inRepairHead;

    if(strstr(plateNum, node->plateNum) != NULL)
    {
        temp = node;
        node = node->next;
        free(temp);
        printf("Successfully returned.\n");
    }

    else
    {
        while(node->next != NULL)
        {
            if(strstr(plateNum, node->next->plateNum) != NULL)
            {
                break;
                found = 1;    
            }

            node = node->next;
        }

        if(found == 1)
        {
            temp = node->next; 
            node->next = node->next->next;
            free(temp);
            printf("Successfully returned.\n");
        }
        else {
            printf("Car with that plate number was not found in our records.\n");
        }
    }

    return inRepairHead;
}

ToRent * transferFromRepair(ToRent * toRentHead, InRepair * inRepairHead, char * plateNum)
{
	InRepair * node;
    ToRent * returnedCar;
    node = inRepairHead;
    int found = 0;

    if(strstr(plateNum, node->plateNum) != NULL)
    {
        returnedCar = createCar(plateNum, node->mileage);
        toRentHead = addToRent(toRentHead, returnedCar);
    }

    else
    {
        while(node->next != NULL)
        {
            if(strstr(plateNum, node->next->plateNum) != NULL)
            {
                break;
                found = 1;    
            }

            node = node->next;
        }

        if(found == 1)
        {
            returnedCar = createCar(plateNum, node->next->mileage);
            toRentHead = addToRent(toRentHead, returnedCar);
        }
        else {
            return toRentHead;
        }
    }
    return toRentHead;
}

void printAll(ToRent * toRentList, Rented * rentedList, InRepair * inRepairList)
{
    ToRent * toRentNode;
    Rented * rentedNode;
    InRepair * inRepairNode;
    char * listString;

    printf("\n********TO*RENT********\n");
    toRentNode = toRentList;
    if(toRentList == NULL)
    {
        printf("Available for Rent List is empty.\n");
    }

    else
    {
        while(toRentNode != NULL)
        {
            listString = printToRent(toRentNode);
            printf("%s\n", listString);
            toRentNode = toRentNode->next;
        }
        /*free(listString); */
    }

    printf("\n********RENTED********\n");
    rentedNode = rentedList;
    if(rentedList == NULL)
    {
        printf("Rented List is empty.\n");
    }
    
    else
    {
        while(rentedNode != NULL)
        {
            listString = printRented(rentedNode);
            printf("%s\n", listString);
            rentedNode = rentedNode->next;
        }
        /*free(listString);*/ 
    }

    printf("\n*******IN*REPAIR*******\n");
    inRepairNode = inRepairList;
    if(inRepairList == NULL)
    {
        printf("Repair List is empty.\n");
    }

    else
    {
        while(inRepairNode != NULL)
        {
            listString = printInRepair(inRepairNode);
            printf("%s\n", listString);
            inRepairNode = inRepairNode->next;
        }
        /*free(listString); */
    }
  }

char * printToRent(ToRent * theList)
{
    char * listString;
    char buffer[MAX_SIZE];

    listString = malloc(sizeof(char)*(strlen(theList->plateNum) + MAX_SIZE));
    strcat(listString, "PLATE #: ");
    strcat(listString, theList->plateNum);
    strcat(listString, "\nMILEAGE (KM): ");
    sprintf(buffer, "%d\n", theList->mileage);
    strcat(listString, buffer);

    return listString;
}

char * printRented(Rented * theList)
{
    char * listString;
    char buffer[MAX_SIZE];

    listString = malloc(sizeof(char)*(strlen(theList->plateNum) + MAX_SIZE));
    strcat(listString, "PLATE #: ");
    strcat(listString, theList->plateNum);
    strcat(listString, "\nMILEAGE (KM): ");
    sprintf(buffer, "%d", theList->mileage);
    strcat(listString, buffer);
    strcat(listString, "\nEXPECTED RETURN DATE (YYMMDD): ");
    sprintf(buffer, "%d\n", theList->returnDate);
    strcat(listString, buffer);

    return listString;
}

char * printInRepair(InRepair * theList)
{
	char * listString;
    char buffer[MAX_SIZE];

    listString = malloc(sizeof(char)*(strlen(theList->plateNum) + MAX_SIZE));
    strcat(listString, "PLATE #: ");
    strcat(listString, theList->plateNum);
    strcat(listString, "\nMILEAGE (KM): ");
    sprintf(buffer, "%d\n", theList->mileage);
    strcat(listString, buffer);

    return listString;
}
/**********************************************************NEWNEWNEW****************************/