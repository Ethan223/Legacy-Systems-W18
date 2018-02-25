/***************************
Name: Ethan Coles
ID: 0843081
Date: 09/29/2014
Assignment Name: Assignment 1, #2
****************************/
#include <stdio.h>
#include <stdlib.h>

int rec(int m, int n);    /*Recursive function that takes 2 input variables, n and m.  Returns an integer.*/

int ackermann()
{
    int i, j;
    int y;

    for(i=0; i<10; i++)
    {
    	for(j=0; j<10; j++)
    	{
    		y = rec(i, j);
            printf("A(%d,%d) = %d\n", i, j, y);
    	}
    }

    return 0;
}

int rec(int m, int n)
{
    if(m == 0 && n >= 0){
    	return n+1;
    }
	
	else if(m > 0 && n == 0) {
		return rec(m-1,1);	    
	}
	
	else{
        return rec(m-1, rec(m, n-1));
	}
}