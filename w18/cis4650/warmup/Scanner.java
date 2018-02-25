/*
Name: Ethan Coles
StudentID: 0843081
File Name: Scanner.java
Description: Scanner class for reading input from stdin.
*/
import java.io.InputStreamReader;
import java.util.*;

public class Scanner {
	private Lexer scanner = null;
	
	public Scanner( Lexer lexer ) {
	    scanner = lexer; 
	}
	
	public Token getNextToken() throws java.io.IOException {
	    return scanner.yylex();
	}
	
	public static void main(String argv[]) {		
		try {
	        Scanner scanner = new Scanner(new Lexer(new InputStreamReader(System.in)));
	        Token tok = null;
	        while((tok=scanner.getNextToken()) != null) {	          
	        	System.out.println(tok);
	        }
	    }
	    catch (Exception e) {
	      System.out.println("Unexpected exception:");
	      e.printStackTrace();
	    }
	}
}
