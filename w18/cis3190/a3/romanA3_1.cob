*>************************************************
*>NAME: ETHAN COLES
*>ID: 0843081
*>FILE: ROMANA3_1.COB
*>DESCRIPTION: CIS*3190 ASSIGNMENT 3, ROMAN NUMERAL CONVERTER
*>************************************************
IDENTIFICATION DIVISION.
PROGRAM-ID. ROMANNUMERALS.
ENVIRONMENT DIVISION.
INPUT-OUTPUT SECTION.
FILE-CONTROL.
    SELECT STANDARD-INPUT ASSIGN TO KEYBOARD.
    SELECT STANDARD-OUTPUT ASSIGN TO DISPLAY.
    SELECT INFILE ASSIGN TO FILENAME
        ORGANIZATION IS LINE SEQUENTIAL
        FILE STATUS IS FSCODE.
DATA DIVISION.
FILE SECTION.
FD STANDARD-INPUT.
    01 STDIN-RECORD   PIC X(80).
FD STANDARD-OUTPUT.
    01 STDOUT-RECORD  PIC X(80).
FD INFILE.
    01 FILE-RECORD PIC X(80).
WORKING-STORAGE SECTION.
77  N    PIC S99 USAGE IS COMPUTATIONAL.
77  DECVALUE PIC S9(8) USAGE IS COMPUTATIONAL.
77  RET  PIC S9 USAGE IS COMPUTATIONAL-3.
01  ARRAY-AREA.
    02 R PIC X(1) OCCURS 30 TIMES.
01  INPUT-AREA.
    02 IN-R PIC X(1) OCCURS 80 TIMES.
01  FILENAME.
    02 FILLER PIC X(1) OCCURS 80 TIMES.
01  TITLELINE.
    02 FILLER PIC X(11) VALUE SPACES.
    02 FILLER PIC X(24) VALUE 'ROMAN NUMBER EQUIVALENTS'.
01  UNDERLINE1.
    02 FILLER PIC X(45) VALUE 
       ' --------------------------------------------'.
01  COL-HEADS.
    02 FILLER PIC X(9) VALUE SPACES.
    02 FILLER PIC X(12) VALUE 'ROMAN NUMBER'.
    02 FILLER PIC X(13) VALUE SPACES.
    02 FILLER PIC X(11) VALUE 'DEC. EQUIV.'.
01  UNDERLINE2.
    02 FILLER PIC X(45) VALUE
       ' ------------------------------   -----------'.
01  PRINT-LINE.
    02 FILLER PIC X VALUE SPACE.
    02 OUT-R  PIC X(30).
    02 FILLER PIC X(3) VALUE SPACES.
    02 OUT-EQ PIC Z(9).
77  ISEOF PIC 9 VALUE 0.
77  FSCODE PIC 9(2).
PROCEDURE DIVISION.
    OPEN INPUT STANDARD-INPUT, OUTPUT STANDARD-OUTPUT.
    
    PERFORM FOREVER        
        *>MAIN MENU
        DISPLAY " "
        DISPLAY UNDERLINE1
        DISPLAY TITLELINE
        DISPLAY UNDERLINE1
        DISPLAY "1) INPUT FROM KEYBOARD"
        DISPLAY "2) INPUT FROM FILE NAME"
        DISPLAY "3) EXIT"
        DISPLAY "> " WITH NO ADVANCING
        
        READ STANDARD-INPUT INTO INPUT-AREA
            AT END CLOSE STANDARD-INPUT, STANDARD-OUTPUT
            STOP RUN
        END-READ
        
*>GET INPUT FROM KEYBOARD--------------------------------------------------
        IF INPUT-AREA = '1'
            DISPLAY " "
            DISPLAY "INPUT ROMAN NUMERALS: " WITH NO ADVANCING
            
            COMPUTE N = 1
            MOVE SPACES TO ARRAY-AREA
        
            READ STANDARD-INPUT INTO INPUT-AREA
                AT END
                CLOSE STANDARD-INPUT, STANDARD-OUTPUT
                STOP RUN
            END-READ
            
            *>ASSIGNS EACH ELEMENT OF THE INPUT STRING TO THE ARRAY PASSED TO CONV
            PERFORM UNTIL IN-R(N) = SPACE
                MOVE IN-R(N) TO R(N)
                COMPUTE N = N + 1
            END-PERFORM

            COMPUTE N = N - 1 
            CALL "CONV" USING ARRAY-AREA, N, RET, DECVALUE
            
            *>SUCCESSFUL CONVERSION, THEN PRINT
            IF RET = 1
                MOVE DECVALUE TO OUT-EQ
                MOVE ARRAY-AREA TO OUT-R
                DISPLAY " "
                DISPLAY COL-HEADS
                DISPLAY UNDERLINE2
                DISPLAY PRINT-LINE
                DISPLAY " "
            END-IF
        
*>GET INPUT FROM A SPECIFIED FILE------------------------------------------
        ELSE
            IF INPUT-AREA = '2'
                DISPLAY " "
                DISPLAY "INPUT FILE NAME: " WITH NO ADVANCING
                READ STANDARD-INPUT INTO FILENAME
                    AT END
                    CLOSE STANDARD-INPUT, STANDARD-OUTPUT
                    STOP RUN
                END-READ
                
                *>READ FILE
                OPEN INPUT INFILE 
                
                IF FSCODE NOT = '00' *>FILE DOES NOT EXIST
                    DISPLAY "ERROR OPENING FILE (STATUS CODE: " FSCODE ")"
                ELSE *>FILE IS SUCCESSFULLY OPENED              
                    DISPLAY " "
                    DISPLAY COL-HEADS
                    DISPLAY UNDERLINE2
                    
                    PERFORM UNTIL ISEOF = 1
                        COMPUTE N = 1
                        MOVE SPACES TO ARRAY-AREA
                        
                        READ INFILE INTO INPUT-AREA
                            AT END COMPUTE ISEOF = 1
                        END-READ
                        
                        IF ISEOF NOT = 1
                            PERFORM UNTIL IN-R(N) = SPACE
                                MOVE IN-R(N) TO R(N)
                                COMPUTE N = N + 1
                            END-PERFORM
                            COMPUTE N = N - 1
                            
                            CALL "CONV" USING ARRAY-AREA, N, RET, DECVALUE
                            
                            IF RET = 1
                                MOVE DECVALUE TO OUT-EQ
                                MOVE ARRAY-AREA TO OUT-R
                                DISPLAY PRINT-LINE
                            END-IF
                        END-IF
                    END-PERFORM
                    
                    CLOSE INFILE
                    COMPUTE ISEOF = 0
                END-IF
*>EXIT OR INVALID OPTION WAS CHOSEN----------------------------------------
            ELSE
                IF INPUT-AREA = '3'
                    EXIT PERFORM
                ELSE
                    DISPLAY 'ERROR: INVALID OPTION'
                END-IF
            END-IF
        END-IF
    END-PERFORM.
