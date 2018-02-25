#define FLAT_RATE 40.00
#define ADD_RATE 0.15
#define MAX_SIZE 51

typedef struct ToRent
{
    char *plateNum;
	int mileage;
	struct ToRent * next;
	
} ToRent;

typedef struct Rented
{
    char *plateNum;
	int mileage;
	int returnDate;
	struct Rented * next;

} Rented;

typedef struct InRepair
{
    char *plateNum;
	int mileage;
	struct InRepair * next;

} InRepair;

typedef struct Car
{
    char *plateNum;
    int mileage;
    int returnDate;
    struct Car *next;

} Car;

/*FUNCTIONS*/


ToRent * addToRent(ToRent * head, ToRent * newCar);  /*Adds to available to rent list*/

Rented * addRented(ToRent * toRentHead, Rented * rentedHead, char * returnDate);  /*Adds element to currently rented list*/

InRepair * addRepair(InRepair * head, InRepair * returnedCar);  /*Adds to repair list*/

ToRent * createCar(char * plateNum, int mileage);  /*Creates a new car to the available to rent list*/

InRepair * createRepairRecord(char * plateNum, int mileage);  /*Creates an element for the repair list*/

void printAll(ToRent * toRentList, Rented * rentedList, InRepair * inRepairList);  /*Prints entire 3 lists*/

char * printToRent(ToRent * theList);  /*Prints available to rent section*/

char * printRented(Rented * theList);  /*Prints currently rented section*/

char * printInRepair(InRepair * theList);  /*Prints repair section*/

ToRent * returnToRent(ToRent * toRentHead, Rented * rentedHead, char * plateNum, int mileage);  /*Transfers element from rented list to available to rent list*/

InRepair * returnToRepair(InRepair * inRepairHead, Rented * rentedHead, char * plateNum, int mileage);  /*Transfers element from rented list to repair list*/

Rented * removeRented(Rented * rentedHead, char * plateNum);  /*Destroys element in rented list*/

InRepair * removeInRepair(InRepair * inRepairHead, char * plateNum);  /*Destroys element in reapair list*/

ToRent * transferFromRepair(ToRent * toRentHead, InRepair * inRepairHead, char * plateNum);  /*Transfers element from repair to available to rent list*/
