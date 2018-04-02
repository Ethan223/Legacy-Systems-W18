--------------------------------------------------------
--Name: Ethan Coles
--ID: 0843081
--File: sieve.adb
--Description: CIS*3190 Assignment 4, Ada implementation
--of Sieve of Eratosthenes algorithm.
--------------------------------------------------------
with ada.Text_IO; use Ada.Text_IO;
with ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with ada.Calendar; use Ada.Calendar;
with ada.Numerics.Elementary_Functions; use Ada.Numerics.Elementary_Functions;
procedure sieve is
    type numset is array(integer range <>) of integer;
    limit : integer;
    limitsq : float;
    outfp : file_type;

    --Time variables
    starttime : time; 
    endtime : time;
    millisec : duration;

    --Asks for upper limit and returns an array of integers of that size
    function inputlimit return numset is
    begin
        put("Enter an upper limit: ");
        get(limit); 

        declare
            primeset : numset(2..limit);
        begin
            primeset  := (2..limit => 0);
            return primeset;
        end;                               
    end inputlimit;

    --Call for input first so the array size can be allocated to the upper limit's size
    primeset : numset := inputlimit;

begin
    --Initialize array of numbers
    for i in 2..limit loop
        primeset(i) := i;
    end loop;

    starttime := clock;
    limitsq := sqrt(float(limit));
    --Main algorithm
    for i in 2..integer(limitsq) loop
        if primeset(i) /= 0 then
            for j in i+1..limit loop
                if primeset(j) mod primeset(i) = 0 then
                    primeset(j) := 0;
                end if;
            end loop;
        end if;
    end loop;

    --Output prime numbers to file
    create(outfp, out_file, "output.txt");

    for i in 2..limit loop
        if primeset(i) /= 0 then
            put(outfp, primeset(i));
            new_line(outfp);
        end if;
    end loop;

    close(outfp);
    put_line("Successfully wrote prime numbers to output.txt.");
    
    --Time data
    endtime := clock;
    millisec := (endtime - starttime)*1000;
    put_line("Algorithm Time: " & duration'image(millisec) & " milliseconds.");
end sieve;
