*>--------------------------------------------------------
*>NAME: ETHAN COLES
*>ID: 0843081
*>FILE: SIEVE.F95
*>DESCRIPTION: CIS*3190 ASSIGNMENT 4, COBOL IMPLEMENTATION
*>OF SIEVE OF ERATOSTHENES ALGORITHM.
*>--------------------------------------------------------
identification division.
program-id. sieve.
environment division.
input-output section.
file-control.
    select standard-input assign to keyboard.
    select standard-output assign to display.
    select outfile assign to "output.txt"
        organization is line sequential
        file status is fscode.
data division.
file section.
fd standard-input.
    01  stdin-record pic x(10).
fd standard-output.
    01 stdout-record  pic x(80).
fd outfile.
    01  file-record pic x(10).
working-storage section.
01  fscode pic 9(2).
01  upperlim pic x(10).
01  input-area.
    02 in-r pic x(1) occurs 80 times.
procedure division.
    open input standard-input, output standard-output.

    display 'Enter an upper limit: ' with no advancing.
    read standard-input into input-area
            at end close standard-input, standard-output
            stop run
    end-read.
