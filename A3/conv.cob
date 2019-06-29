*>************************************************
*>NAME: ETHAN COLES
*>ID: 0843081
*>FILE: CONV.COB
*>DESCRIPTION: SUBROUTINE FOR ROMAN NUMERAL CONVERTER
*>************************************************
IDENTIFICATION DIVISION.
PROGRAM-ID. CONV.
ENVIRONMENT DIVISION.
INPUT-OUTPUT SECTION.
FILE-CONTROL.
    SELECT STANDARD-OUTPUT ASSIGN TO DISPLAY.
DATA DIVISION.
FILE SECTION.
FD STANDARD-OUTPUT.
    01 STDOUT-RECORD  PICTURE X(80).
WORKING-STORAGE SECTION.
77  I    PIC S99 USAGE IS COMPUTATIONAL.
77  PREV PIC S9(8) USAGE IS COMPUTATIONAL. *>HOLDS PREVIOUS SUM USED FOR NUMERALS SUCH AS 'IV'
77  D    PIC S9(4) USAGE IS COMPUTATIONAL. *>HOLDS TEMPORARY SUM OF CONVERTED INPUT
77  INPUTERR PIC 9. *>FLAG SET WHEN INVALID INPUT OCCURS
01  ERRORMESS.      *>ERROR MESSAGE WHEN INVALID INPUT IS PASSED IN
    02 FILLER PICTURE X(22) VALUE ' ILLEGAL ROMAN NUMERAL'.

LINKAGE SECTION.
77  NUMLENGTH PIC S99 USAGE IS COMPUTATIONAL.  *>LENGTH OF ROMAN NUMERAL
77  RETURNVAL PIC S9 USAGE IS COMPUTATIONAL-3. *>SUBROUTINE RETURN VALUE. 1 ON SUCCESS, 2 ON FAILURE
77  DECVALUE PIC S9(8) USAGE IS COMPUTATIONAL. *>DECIMAL EQUIVALENT NUMBER
01  ARRAY-AREA.                                    *>STRING OF ROMAN NUMERALS
    02 S PIC X(1) OCCURS 30 TIMES.

PROCEDURE DIVISION USING ARRAY-AREA, NUMLENGTH, RETURNVAL, DECVALUE.
    COMPUTE DECVALUE = 0.
    COMPUTE PREV = 1001.
    COMPUTE INPUTERR = 0.
    
    *>ITERATES STRING OF ROMAN NUMERALS AND COMPUTES THE SUM
    PERFORM VARYING I FROM 1 BY 1 UNTIL I > NUMLENGTH
        IF S(I) = 'I' OR S(I) = 'I'
            COMPUTE D = 1
        ELSE
            IF S(I) = 'V' OR S(I) = 'V'
                COMPUTE D = 5
            ELSE
                IF S(I) = 'X' OR S(I) = 'X'
                    COMPUTE D = 10
                ELSE
                    IF S(I) = 'L' OR S(I) = 'L'
                        COMPUTE D = 50
                    ELSE
                        IF S(I) = 'C' OR S(I) = 'C'
                            COMPUTE D = 100
                        ELSE
                            IF S(I) = 'D' OR S(I) = 'D'
                                COMPUTE D = 500
                            ELSE
                                IF S(I) = 'M' OR S(I) = 'M'
                                    COMPUTE D = 1000
                                ELSE
                                    COMPUTE INPUTERR = 1
                                    EXIT PERFORM
                                END-IF
                            END-IF
                        END-IF
                    END-IF
                END-IF
            END-IF
        END-IF

        COMPUTE DECVALUE = DECVALUE + D
        
        *>PREVIOUS NUMERAL SMALLER THAN CURRENT
        IF D > PREV
            COMPUTE DECVALUE = DECVALUE - 2 * PREV
        END-IF
        COMPUTE PREV = D
    END-PERFORM.
    
    IF INPUTERR = 1
        OPEN OUTPUT STANDARD-OUTPUT
        WRITE STDOUT-RECORD FROM ERRORMESS AFTER ADVANCING 1 LINE
        COMPUTE RETURNVAL = 2
        CLOSE STANDARD-OUTPUT
    ELSE
        COMPUTE RETURNVAL = 1
    END-IF.

GOBACK. 
