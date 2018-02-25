*************************
CIS*4650 Warm-up Assignment
Name: Ethan Coles
StudentID: 0843081
*************************

What the program does:
- Program is a Scanner which takes SGML documents as input.
- The SGML contents are broken up into tokens and relevant ones are output.
- Program uses JFlex to process the input.

Assumptions and Limitations:
- Assumed that when the stack is empty, information is filtered out and irrelevant.
- When an close tag is read and does not match what is on top of the stack and error is reported and scanning resumes.
- When EOF is reached, the remaining tags on the stack are output to the console if an error was reported.
- No known limitations.

How to build and test the program:
1. To build, type `make`
2. To run, type `java Scanner < {TEST_FILE}`

Possible improvements for future:
-Better error handling by handling it gracefully.
-Instead of continuing until EOF, have program stop at an error and output what line it occurred on in the SGML file.
(Not required by the assignment spec though).


*********************************************************************************************************************
Test Plan:
				Input				|				Result				|				Pass/Fail?
<date>								|OPEN-DATE							|PASS
<TEXT align="left">					|OPEN-TAG(<TEXT align="left">)		|PASS
<   TEXT  >							|OPEN-TEXT							|PASS
</DOcNo>							|CLOSE-DOCNO						|PASS
</Tag1>								|CLOSE-TAG(</TAG1>)					|PASS
< /DATE    >						|CLOSE-DATE							|PASS
John								|WORD(John)							|PASS
4mp3								|WORD(4mp3)							|PASS
-JOHN								|PUNCTUATION(-)WORD(JOHN)			|PASS
1739								|NUMBER(1739)						|PASS
+2.1								|NUMBER(+2.1)						|PASS
-273.15								|NUMBER(-273.15)					|PASS
O'Hanlon's							|APOSTROPHIZED(O'Hanlon's)			|PASS
''									|APOSTROPHIZED(')APOSTROPHIZED(')	|PASS
Words-with-hyph'ens					|APOSTROPHIZED(Words-with-hyph'ens) |PASS
Words-with-hyphens					|HYPHENATED(Words-with-hyphens)		|PASS
-FIRST								|PUNCTUATION(-)\nWORD(FIRST)		|PASS
--									|PUNCTUATION(-)\nPUNCTUATION(-)		|PASS
#									|PUNCTUATION(#)						|PASS
two words							|WORD(two)\nWORD(words)				|PASS
<DOC>								|OPEN-DOC							|PASS
<DOCNO>								|OPEN-DOCNO							|PASS
<TEXT>								|OPEN-TEXT							|PASS
<DATE>								|OPEN-DATE							|PASS
<LENGTH>							|OPEN-LENGTH						|PASS
<HEADLINE>							|OPEN-HEADLINE						|PASS					