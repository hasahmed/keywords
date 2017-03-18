keywords:
	gcc -o keywords utilfuncs.c keywords.c
	gcc -o wordkeys wordkeys.c
clean:
	rm keywords wordkeys *.txt
