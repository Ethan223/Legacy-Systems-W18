/***************************
Name: Ethan Coles
ID: 0843081
Date: 09/29/2014
Assignment Name: Assignment 1, #3
****************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define EPSLN 0.000001

double newSqrt(double x);    /*This function approximates the square root of the input variable(s), x using Newton's Method.  Takes input variable as parameter, returns approximation.*/

double newSqrtRecurion(double x, double a);    /*This function approximates the square root of the input variable(s), x using Newton's Method with recursion.  It takes 2 parameters, the input variable and the initial approximation, and returns the approximation.*/

void newton()
{
    double x[10] = {10, 36, 45, 81, 100, 134, 223, 260, 266, 300};
    double approx;
    int i;

    /*WITH RECURSION*/
    printf("*****************RECURSION************************\n");

    for (i=0; i<10; i++)
    {
        printf("Number: %lg\n", x[i]);
        approx = x[i]/2;
        approx = newSqrtRecurion(x[i], approx);
        printf("Approximation: %lf\n\n", approx);
    }

    /*WITHOUT RECUSRION*/
    printf("****************NON-RECURSION*******************\n");

    for(i=0; i<10; i++)
    {
        printf("Number: %lg\n", x[i]);
        approx = newSqrt(x[i]);
        printf("Approximation: %lf\n\n", approx);     
    }
}

double newSqrt(double x)
{
    double a;
    double result;

	a = x/2;

    do {
        result = (a*a) - x;

        if(result < 0) {
            result = -result;
        }

        if(result <= EPSLN) {
            break;
        }

        a = (a+(x/a))/2;

    } while(result > EPSLN);
    
    return a;
}

double newSqrtRecurion(double x, double a)
{
    double result;

    result = (a*a) - x;

    if(result < 0) {
        result = -result;
    }
    
    if(result <= EPSLN) {
        return a;
    }
    else {
        a = (a+(x/a))/2;
        a = newSqrtRecurion(x, a);
    }

    return a;
}