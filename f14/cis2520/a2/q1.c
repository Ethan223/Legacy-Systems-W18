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

void printMenu();

int main(int argc, char **argv)
{
    char choice[MAX_SIZE];
    char plateNum[MAX_SIZE];
    char inputMileage[MAX_SIZE];
    char returnDate[MAX_SIZE];
    double charge = 0;
    double income = 0;
    
    FILE * records;
    char * readLine;
    char * plateNumPtr;
    char * mileagePtr;

    ToRent * toRentHead = NULL;
    ToRent * newToRentHead = NULL;
    ToRent * newCar;

    Rented * rentedHead = NULL;

    InRepair * inRepairHead = NULL;

    if (argc != 2 && argc != 1)
    {
        printf("Usage: ./q1 filename\nor,\nUsage: ./q1\n");
        return -1;
    }

    records = fopen(argv[1], "r");
    readLine = malloc(sizeof(char)*151);

    if (records == NULL && argc == 2)
    {
        printf("Error opening file.\n");
        return -1;
    }
    
    fgets(readLine, MAX_SIZE, records);
    while(!feof(records))
    {
        plateNumPtr = strtok(readLine, ",");
        mileagePtr = strtok(NULL, ",");

        newCar = createCar(plateNumPtr, atoi(mileagePtr));
        toRentHead = addToRent(toRentHead, newCar);

        fgets(readLine, MAX_SIZE, records);
    }

    /*******************************************************************************/

    do {
        printMenu();
        fgets(choice, MAX_SIZE, stdin);

        if(choice[0] == '1' && choice[1] == '\n')
        {
            printf("Enter the license plate number: ");
            fgets(plateNum, MAX_SIZE, stdin);
            strtok(plateNum, "\n");
            
            printf("Enter the mileage of the car: ");
            fgets(inputMileage, MAX_SIZE, stdin);
            strtok(inputMileage, "\n");

            newCar = createCar(plateNum, atoi(inputMileage));

            /*Check if newCar is NULL?*/

            toRentHead = addToRent(toRentHead, newCar);

            printf("Successfully added car to rented list.\n");
        }

        else if(choice[0] == '2' && choice[1] == '\n')
        {
            if(rentedHead == NULL)    /*Checks if empty*/
            {
                printf("Rented list is empty.\n");
                printf("Our records show that no car is currently being rented.\n");
            }
            
            else
            {
                
                printf("Enter the license plate number: ");
                fgets(plateNum, MAX_SIZE, stdin);
                
                do {
                    printf("Enter the mileage of the car: ");
                    fgets(inputMileage, MAX_SIZE, stdin);
                } while(inputMileage < 0);

                toRentHead = returnToRent(toRentHead, rentedHead, plateNum, atoi(inputMileage));
                rentedHead = removeRented(rentedHead, plateNum);

                if(atoi(inputMileage) > 100)
                {
                    charge = FLAT_RATE + ((atoi(inputMileage) - 100)*ADD_RATE);
                    printf("The charge for renting this car is $%.2lf\n", charge);
                    income = income + charge;
                }
                else if(atoi(inputMileage) > 0 && atoi(inputMileage) <= 100)
                {
                    charge = FLAT_RATE;
                    printf("The charge for renting this car is $%.2lf\n", charge);
                    income = income + charge;
                }

            }
        }

        else if(choice[0] == '3' && choice[1] == '\n')
        {
        	if(rentedHead == NULL)
            {
                printf("Rented list is empty.\n");
                printf("Our records show that no car is currently being rented.\n");
            }
            
            else
            {
                printf("Enter the license plate number: ");
                fgets(plateNum, MAX_SIZE, stdin);
            
                do {
                    printf("Enter the mileage of the car: ");
                    fgets(inputMileage, MAX_SIZE, stdin);
                } while(inputMileage < 0);

                inRepairHead = returnToRepair(inRepairHead, rentedHead, plateNum, atoi(inputMileage));
                rentedHead = removeRented(rentedHead, plateNum);

                if(atoi(inputMileage) > 100)
                {
                    charge = FLAT_RATE + ((atoi(inputMileage) - 100)*ADD_RATE);
                    printf("The charge for renting this car is $%.2lf\n", charge);
                    income = income + charge;
                }
                else if(atoi(inputMileage) > 0 && atoi(inputMileage) <= 100)
                {
                    charge = FLAT_RATE;
                    printf("The charge for renting this car is $%.2lf\n", charge);
                    income = income + charge;
                }
            }
        }

        else if(choice[0] == '4' && choice[1] == '\n')
        {
        	if(toRentHead == NULL)
            {
                printf("Out records indicate no cars are available for rent.\n");
            }

            else
            {
                printf("Enter the license plate number: ");
                fgets(plateNum, MAX_SIZE, stdin);

                toRentHead = transferFromRepair(toRentHead, inRepairHead, plateNum);
                inRepairHead = removeInRepair(inRepairHead, plateNum);
            }
        }

        else if(choice[0] == '5' && choice[1] == '\n')
        {
            if(toRentHead == NULL)
            {
                printf("Out records indicate no cars are available for rent.\n");
            }

            else
            {
                do {
                    printf("Enter the expected return date (yymmdd): ");
                    fgets(returnDate, MAX_SIZE, stdin);
                
                    if(strlen(returnDate) != 7)
                    {
                        printf("Make sure zeros are put in front of year, month, and date numbers less than 10 and the value is exactly 6 digits.\n");
                    }
                } while(strlen(returnDate) != 7);
            
                rentedHead = addRented(toRentHead, rentedHead, returnDate);
                newToRentHead = toRentHead->next;    /*Deletes first record of available to rent list.*/
                free(toRentHead);
                toRentHead = newToRentHead;
                printf("Successfully transfered to rented list.\n");
            }
        }

        else if(choice[0] == '6' && choice[1] == '\n')
        {
            printAll(toRentHead, rentedHead ,inRepairHead);
        }

        else if(choice[0] == '7' && choice[1] == '\n')
        {
        	printf("Total Income: $%.2lf\n", income);
            return 0;
        }

        else
        {
            printf("Invalid option. Try again.\n");
        }

    } while (!(choice[0] == '7' && choice[1] == '\n'));

	return 0;
}

void printMenu()
{
	printf("\n********CAR RENTAL********\n");
	printf("1)Add new car to available-for-rent list\n");
	printf("2)Add returned car to available-for-rent list\n");
	printf("3)Add returned car to repair list\n");
	printf("4)Transfer car from repair list to available-for-rent list\n");
	printf("5)Rent first available car\n");
	printf("6)Print all the lists\n");
	printf("7)Quit\n");
	printf("> ");
}