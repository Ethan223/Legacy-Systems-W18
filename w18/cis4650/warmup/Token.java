/*
Name: Ethan Coles
StudentID: 0843081
File Name: Token.java
Description: Token class for printing out token types for scanner.
*/
class Token {
    public final static int OPEN_TAG = 0;
    public final static int CLOSE_TAG = 1;
    public final static int WORD = 2;
    public final static int NUMBER = 3;
    public final static int HYPHENATED = 4;
    public final static int APOSTROPHIZED = 5;
    public final static int PUNCTUATION = 6;

    public int m_type;
    public String m_value;
    public int m_line;
    public int m_column;
  
    Token (int type, String value, int line, int column) {
        m_type = type;
        m_value = value;
        m_line = line;
        m_column = column;
    }

    public String toString() {
        switch(m_type) {
            case OPEN_TAG:
                switch(m_value.toUpperCase().replaceAll(" ", "")) {
                    case "<DOC>":
                        return "OPEN-DOC";
                    case "<DOCNO>":
                        return "OPEN-DOCNO";
                    case "<TEXT>":
                        return "OPEN-TEXT";
                    case "<DATE>":
                        return "OPEN-DATE";
                    case "<LENGTH>":
                        return "OPEN-LENGTH";
                    case "<HEADLINE>":
                        return "OPEN-HEADLINE";
                    default: 
                        return "OPEN-TAG(" + m_value + ")";
                }
            case CLOSE_TAG:
                switch(m_value.toUpperCase().replaceAll(" ", "")) {
                    case "</DOC>":
                        return "CLOSE-DOC";
                    case "</DOCNO>":
                        return "CLOSE-DOCNO";
                    case "</TEXT>":
                        return "CLOSE-TEXT";
                    case "</DATE>":
                        return "CLOSE-DATE";
                    case "</LENGTH>":
                        return "CLOSE-LENGTH";
                    case "</HEADLINE>":
                        return "CLOSE-HEADLINE";
                    default: 
                        return "CLOSE-TAG(" + m_value + ")";
                }
            case WORD:
                return "WORD(" + m_value + ")";
            case NUMBER:
                return "NUMBER(" + m_value + ")";
            case HYPHENATED:
                return "HYPHENATED(" + m_value + ")";
            case APOSTROPHIZED:
                return "APOSTROPHIZED(" + m_value + ")";    
            case PUNCTUATION:
                return "PUNCTUATION(" + m_value + ")";
            default:
                return "UNKNOWN(" + m_value + ")";
        }
    }
}