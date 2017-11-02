OBJS = utilfuncs.o keywords.o
CC = gcc


keywords:
	gcc -o keywords utilfuncs.c keywords.c -Wall
	gcc -o wordkeys wordkeys.c


