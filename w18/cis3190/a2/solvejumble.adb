--------------------------------------------------
--Name: Ethan Coles
--ID: 0843081
--File: solvejumble.adb
--Description: CIS*3190 Assignment 2, Word Jumble using Ada.
--------------------------------------------------
with ada.Text_IO; use Ada.Text_IO;
with ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with ada.Float_Text_IO; use Ada.Float_Text_IO;
with ada.characters.handling; use ada.characters.handling;
with ada.strings.unbounded; use ada.strings.unbounded;
with ada.strings.unbounded.Text_IO; use ada.strings.unbounded.Text_IO;
procedure solvejumble is
    type strArray is array(integer range <>) of unbounded_string;
    jumble : unbounded_string;
    match : boolean := false;  
    

    function buildlexicon return strArray is
        infp : file_type;
        i : integer := 1;
        str : unbounded_string;
    begin
        open(infp, in_file, "/usr/share/dict/words");        
        while not end_of_file(infp) loop
            str := get_line(infp);
            
            if length(str) < 7 then
                i := i + 1; --Finds number of words up to 6 letters for getting dictionary array bounds
            end if;
        end loop;        

        reset(infp, in_file); --Let program read file from beginning again
        
        declare --Reads file a second time and stores the words in an array of unbounded strings
            dictionary : strArray(1..i-1);
        begin       
            i := 1;
            while not end_of_file(infp) loop
                str := get_line(infp);

                if length(str) < 7 then
                    dictionary(i) := str;
                    i := i + 1;
                end if;
            end loop;        
            
            close(infp);
            return dictionary;
        end;
    end buildlexicon;

    dictionary : strArray := buildlexicon;

    function inputjumble return unbounded_string is
        input : unbounded_string;

        --Helper funtion for making sure only letters are entered
        function validateinput return boolean is
        begin
            if length(input) > 6 then
                put_line("Error: Word jumbles can only be at most 6 characters");
                put_line("-----------------------------------------");
                return false;
            else
                for i in 1..length(input) loop
                    if not is_basic(element(input, i)) then
                        put_line("Error: Word jumbles can only contain letters");
                        put_line("-----------------------------------------");
                        return false;
                    end if;
                end loop;
            end if;

            return true;
        end validateinput;

    begin
        loop
            new_line;
            put("Enter a word jumble (or '0' to exit): ");
            get_line(input);

            --Convert unbounded string to lower case
            input := to_unbounded_string(to_lower(to_string(input)));

            if input = "0" then
                return input;
            elsif validateinput then
                return input;
            end if;
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
                    match := true;
                    put(anagram);
                    put(" ");
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
    loop
        jumble := inputjumble;
        exit when jumble = "0";
            
        put(to_upper(to_string(jumble)));
        put(":    ");
        generateanagram(jumble, 1);        

        if not match then
            put("No matching anagrams found.");
        end if;
        new_line;
        put_line("-----------------------------------------");

        match := false;  --Reset for next input jumble
    end loop;

    put_line("Exiting program...");
end solvejumble;


--for i in 1..20 loop
--    put("dictionary[");
--    put(i, 1);
--    put("] = ");
--    put_line(dictionary(i));
--end loop;

--while i <= length(jumbleset) loop
--    if element(jumbleset, i) = ' ' then
--      put_line(slice(jumbleset, j, i-1));
--        j := i + 1;

--      while element(jumbleset, j) = ' ' loop
        --  i := i + 1;
        --    j := j + 1;
      --end loop;
    --end if;

    --i := i + 1;
--end loop;

        --put(slice(jumbleset, j, i-1));