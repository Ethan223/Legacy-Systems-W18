*>--------------------------------------------------------
*>name: ethan coles
*>id: 0843081
*>file: sieve.f95
*>description: cis*3190 assignment 4, cobol implementation
*>of sieve of eratosthenes algorithm.
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
fd outfile.
    01  file-record pic Z(10).
working-storage section.
01  fscode pic 9(2).
01  upperlim pic S9(10).
01  quotient pic 9(10).
01  rem pic 9(10).
01  input-area.
    02  in-r pic x(1) occurs 80 times.
01  primeset.
    02  pr pic 9(10) occurs 2 to 999999999 times depending on upperlim.
01  i pic 9(10).
01  j pic 9(10).
01  offset pic 9(10).
procedure division.
    open input standard-input, output standard-output.

    display 'enter an upper limit: ' with no advancing.
    read standard-input into upperlim
            at end close standard-input, standard-output
            stop run
    end-read.
    
    if upperlim < 2 or upperlim > 999999999
        display 'error: invalid upper limit'
        stop run
    end-if.
    
    perform varying i from 1 by 1 until i >= upperlim
        compute pr(i) = i + 1
    end-perform.
    
    perform varying i from 1 by 1 until i >= upperlim
        if pr(i) is not = 0
            compute offset = i + 1
            
            perform varying j from offset by 1 until j >= upperlim                
                if pr(i) is not = 0                    
                    divide pr(i) into pr(j) giving quotient remainder rem
                else
                    compute rem = 1
                end-if

                if rem is equal to 0
                    compute pr(j) = 0
                end-if
            end-perform
        end-if
    end-perform.
  
    *>Write prime numbers to file
    open output outfile.
    
    perform varying i from 1 by 1 until i >= upperlim
        if pr(i) is not equal to 0
            compute file-record = pr(i)
            write file-record
            end-write
        end-if        
    end-perform.
    
    close outfile.
