/*
  Name: Ethan Coles
  StudentID: 0843081
  File Name: sgml.flex
  Description: JFlex specification for SGML
*/
   
import java.util.ArrayList;

%%
   
%class Lexer
%type Token
%line
%column

%{
	private static ArrayList<String> tagStack = new ArrayList<String>();  //Global stack keeping track of SGML tags
	private static boolean relevant = true;  //Global flag that determines if information is relevant
	private static boolean error = false;  //Flag set if error occurs before EOF
  	
  	/*Pushes SGML tags on the global stack to keep track of the structure.
  	* Is called when an open tag is read from stdin.
  	**/
  	private static void pushTagName(String openTag) {
  		String[] words;
  		
	    openTag = openTag.toUpperCase();
	    
	    //Tag has attributes
	    if(openTag.contains("=")) {
	    	openTag = openTag.replaceAll("[<>]", "");
	    	words = openTag.split("\\s+");
	    	
	    	if(openTag.charAt(0) == ' ')  //Is there whitespace before the tag?
	    		openTag = words[1];  //Get second token in word list, first will be empty string
	    	else
	    		openTag = words[0];  //Otherwise, the first token will be the tag name
	    }
	    
	    //Tag does not have attributes
	    else {
	    	openTag = openTag.replaceAll("[<> ]", "");	        	    
	    }
	    
	    tagStack.add(0, openTag);
	    relevant = checkTagRelevance();
  	}
  	
  	/*Removes SGML tags on the global stack to keep track of the structure.
  	* Is called when a close tag is read from stdin. If the close tag does not match with
  	* what is on the top of the stack, the element is not popped and an error message
  	* is sent to stderr.
  	**/
  	private static void popTagName(String closeTag) {	            	
	    closeTag = closeTag.replaceAll("[/<> ]", "");
	    closeTag = closeTag.toUpperCase();
	    
	    if(!tagStack.isEmpty()) {
			//The closing tag matches with the tag at the top of the stack
			if(closeTag.equals(tagStack.get(0))) {
		    	tagStack.remove(0);
		    	relevant = checkTagRelevance();
			}
		    else {
		    	error = true;
		    	System.err.println("Error: Close tag '</" + closeTag + ">' not matched. Expecting: '</" + tagStack.get(0) + ">'.");
		    }
	    }
	    else {
	    	error = true;
	    	System.err.println("Error: Read close tag when stack was empty.");
	    }
  	}
  	
  	/*Checks the global stack if an irrelevant tag is pushed on it.
  	* Returns false if at least 1 irrelevant tag is on the stack, true otherwise.
  	**/
  	private static boolean checkTagRelevance() {
  		for(int i=0; i<tagStack.size(); i++) {
  			if(!tagStack.get(i).equals("DOC") && !tagStack.get(i).equals("DOCNO") && !tagStack.get(i).equals("TEXT") &&
  			   !tagStack.get(i).equals("DATE") && !tagStack.get(i).equals("HEADLINE") && !tagStack.get(i).equals("LENGTH") &&
  			   !tagStack.get(i).equals("P"))
  				return false;	
  		}
  		
  		return true;
  	}
  	
  	/*Indicator function used by new tokens whether they can output or not.
  	* Returns the current boolean value of relevant.
  	**/
  	private static boolean isRelevant() {
  		return relevant;
  	}
  	
  	/*Prints out tags currently stored on the stack to stderr.*/
  	private void printStack() {
  		System.err.println("---UNMATCHED-TAGS---");
	    for(int i=0; i<tagStack.size(); i++) {
	    	System.err.println("'" + tagStack.get(i) + "'");
	    }
	    System.err.println("--------------------\n");
	}

%};
    
%eofval{
  System.out.println("*** end of file reached");
  if(error)
  	printStack();
  
  return null;
%eofval};

/*A line terminator is a \r (carriage return), \n (line feed), or\r\n.*/
LineTerminator = \r|\n|\r\n
   
/* White space is a line terminator, space, tab, or form feed.*/
WhiteSpace = {LineTerminator} | [ \t\f]

/*NUMBER: Integers and real numbers with possible positve and negative signs.*/
Number = ((\+|\-)?[0-9]+)|((\+|\-)?[0-9]+\.?[0-9]+)

/*WORD: Strings of letters and digits separated by spaces, tabs, newlines, and
 most of the punctuation marks.*/
Word = [a-zA-Z0-9]*[a-zA-Z]+[a-zA-Z0-9]*

/*HYPHENATED: Words with hyphens between them.*/
Hyphenated = [a-zA-Z0-9]+(-[a-zA-Z0-9]+)+

/*APOSTROPHIZED: Words separated by apostrophes. This is the expression for a word with
 apostrophes in the character classes.*/
Apostrophized = [a-zA-Z0-9][a-zA-Z0-9-]*'([a-zA-Z0-9-]+'?)*

/*OPEN-TAG and CLOSE-TAG*/
OpenTag = <[ ]*[a-zA-Z0-9_]+([ ]+[a-zA-Z0-9_]+=\"[a-zA-Z0-9_]*\")*[ ]*>
CloseTag = <[ ]*\/[ ]*[a-zA-Z0-9_]+[ ]*>

/*PUNCTUATION: Any symbol not contributing to the tokens above*/
Punctuation = [^a-zA-Z0-9\+\n\r\t\f ]

%%

/*Regular Expressions*/
{OpenTag}       {	Token token = new Token(Token.OPEN_TAG, yytext(), yyline, yycolumn);
					pushTagName(token.m_value);
					
					if(isRelevant())
						return token;  }

{CloseTag}      { 	Token token = new Token(Token.CLOSE_TAG, yytext(), yyline, yycolumn);					
					boolean wasRelevant = isRelevant();  //Flag for checking if the tag being popped is relevant
					
					popTagName(token.m_value);
					
					if(wasRelevant)
						return token;  }

{Word}          { 	if(isRelevant())
						return new Token(Token.WORD, yytext(), yyline, yycolumn); }

{Number}        { 	if(isRelevant())
						return new Token(Token.NUMBER, yytext(), yyline, yycolumn); }

{Hyphenated}    { 	if(isRelevant())
						return new Token(Token.HYPHENATED, yytext(), yyline, yycolumn); }

{Apostrophized} { 	if(isRelevant())
						return new Token(Token.APOSTROPHIZED, yytext(), yyline, yycolumn); }

{WhiteSpace}*   { /* skip whitespace */ }

{Punctuation}   {	if(isRelevant())
						return new Token(Token.PUNCTUATION, yytext(), yyline, yycolumn); }