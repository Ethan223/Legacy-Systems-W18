all: c fortran ada cobol

c: sieve.c
	gcc -Wall -ansi sieve.c -o c -lm

fortran: sieve.f95
	gfortran -Wall sieve.f95 -o fortran

ada: sieve.adb
	gnatmake sieve.adb -o ada

cobol: sieve.cob 
	cobc -x -free -Wall sieve.cob -o cobol
	

clean:
	rm -f fortran ada cobol c python
