/***************************************************
Name: Ethan Coles
ID: 0843081
File: sieve.c
Description: CIS*3190 Assignment 4, C implementation
of Sieve of Eratosthenes algorithm.
***************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

/*Initializes array of integers from 2 to the upper limit.*/
int* populatePrimes(int* prime, int upperLim) {
    int i;

    for(i=0; i<upperLim; i++)
        prime[i] = i+2;

    return prime;
}

/*Prints out the prime numbers to an ASCII file.
Any remaining numbers in the prime array that are not 0 are written.*/
void printPrimes(FILE* fp, int* prime, int length) {
    int i;

    for(i=0; i<length; i++) {
        if(prime[i] != 0)
            fprintf(fp, "%d\n", prime[i]);
    }
}

int main(int argc, char *argv[]) {
    FILE* fp;        /*File pointer*/
    int* prime;      /*Array containing prime numbers*/
    int limit, i, j; /*Upper limit of prime numbers to output*/
    char buffer[80]; /*Input buffer*/

    clock_t begin;
    clock_t end;
    double timeExec;

    printf("Enter an upper limit: ");
    fgets(buffer, 80, stdin);

    i = 0; /*Verify input is a number*/
    while(buffer[i] != '\n') {
        if(!isdigit(buffer[i])) {
            fprintf(stderr, "Error: Not a decimal value\n");
            return -1;
        }

        i++;
    }

    limit = atoi(buffer);

    if(limit < 2 || limit > 999999999) {
        fprintf(stderr, "Error: Invalid limit value\n");
        return -1;
    }
    
    begin = clock();
    
    limit -= 1; /*1 less array element because starting at 2*/
    prime = malloc(sizeof(int)*limit);
    prime = populatePrimes(prime, limit);

    for(i=0; i<sqrt(limit); i++) { /*Main algorithm for Sieve of Eratosthenes*/
        if(prime[i] != 0) {
            for(j=i+1; j<limit; j++) {
                if(prime[j]%prime[i] == 0)
                    prime[j] = 0;
            }
        }
    }

    fp = fopen("output.txt", "w"); /*Write to file*/
    if(fp == NULL) {
        fprintf(stderr, "Error opening file.\n");
        free(prime);
    }

    printPrimes(fp, prime, limit);
    fclose(fp);

    end = clock();
    timeExec = (double)(end - begin)/CLOCKS_PER_SEC;

    printf("Successfully wrote prime numbers to output.txt.\n");
    printf("Algorithm Time: %lf seconds.\n", timeExec);
    free(prime);    
    return 0;
}
