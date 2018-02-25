with ada.Text_IO; use Ada.Text_IO;
with ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with ada.Float_Text_IO; use Ada.Float_Text_IO;
with ada.characters.handling; use ada.characters.handling;
with ada.strings.unbounded; use ada.strings.unbounded;
with ada.strings.unbounded.Text_IO; use ada.strings.unbounded.Text_IO;
with ada.command_line; use ada.command_line;
procedure solvejumble is
    jumbleset : array(1..argument_count) of unbounded_string;
    type lexicon is array(integer range <>) of unbounded_string;    
    

    function buildLEXICON return lexicon is
        infp : file_type;
        i : integer := 1;
        str : unbounded_string;
    begin
        open(infp, in_file, "/usr/share/dict/words");        
        while not end_of_file(infp) loop
            str := get_line(infp);
            i := i + 1;
        end loop;        
        
        reset(infp, in_file);
        
        declare
            dictionary : lexicon(1..i-1);
        begin       
            i := 1;
            while not end_of_file(infp) loop
                dictionary(i) := get_line(infp);
                i := i + 1;
            end loop;        
            
            close(infp);
            return dictionary;
        end;
    end buildLEXICON;

    dictionary : lexicon := buildLEXICON;

    procedure inputjumble is
    begin
        for i in 1..argument_count loop
            jumbleset(i) := to_unbounded_string(to_lower(argument(i)));
        end loop;
    end inputjumble;

    procedure swap(anagram : in out unbounded_string; a : in integer; b : in integer) is
        tmp : character;
    begin
        tmp := element(anagram, a);
        replace_element(anagram, a, element(anagram, b));
        replace_element(anagram, b, tmp);
    end swap;

    procedure generateanagram(anagram : in out unbounded_string; i : in integer) is
        j : integer;
        
        procedure findanagram is        
        begin
            for i in 1..dictionary'last loop
                if dictionary(i) = anagram then
                    put_line(anagram);
                end if; 
            end loop;
        end findanagram;

    begin
        if i = length(anagram)  then
            findanagram;
        else
            j := i;
            for j in i..length(anagram) loop
                swap(anagram, i, j);
                generateanagram(anagram, i+1);
                swap(anagram, i, j);
            end loop;
        end if;
    end generateanagram;

begin
    if argument_count = 0 then
        put_line("Usage: ./solvejumble <anagram_1> <anagram_2> ... <anagram_n>");
        return;
    end if;

    inputjumble;
    for i in 1..jumbleset'length loop
        generateanagram(jumbleset(i), 1);
    end loop;
end solvejumble;


--for i in 1..20 loop
--    put("dictionary[");
--    put(i, 1);
--    put("] = ");
--    put_line(dictionary(i));
--end loop;

--put("Enter a set of jumbles: ");
        --get_line(jumbleset);

        --while i <= length(jumbleset) loop
        --    if element(jumbleset, i) = ' ' then
          --      put_line(slice(jumbleset, j, i-1));
            --    j := i + 1;

              --  while element(jumbleset, j) = ' ' loop
                  --  i := i + 1;
                --    j := j + 1;
                --end loop;
           -- end if;

            --i := i + 1;
        --end loop;

        --put(slice(jumbleset, j, i-1));