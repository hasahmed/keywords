Overview:
This is just a fun little program that lets you enter a phone number, and it writes the words (if any) that can be spelled with that phone number to a file.

Useage:

1. Compile using the makefile.
2. Run by typing ./keywords 5555555
3. hack away!


More Stuff:

You can specify your own dictionary by using the -d option. By default it uses the dict/7letterdict.txt.
The way the program is written now every word in the dictonary must be 7 letters. In order to convert a dictonary containing words of every size, to a dictionary containing words with only 7 letters, there is a program called filter in the dict folder which will do this. Run the program with no arguments for a synopsis. 
Be careful putting the arguments in the correct order using filter, because there is not protection from overwriting a dictonary file as the output file.

Future Plans:

I intend try to optimize the program in serveral ways, as well as modify it to search for matches of 3 and 4 letter words. In addition to whatever else I feel like adding. 
