CC = gcc
OBJS = keywords.o utilfuncs.o
CFLAGS = -Wall

num1 = 538-8823
num2 = 999-9982

keywords: $(OBJS)
	$(CC) -o keywords $(OBJS) $(CFLAGS)

wordkeys : wordkeys.o
	$(CC) -o wordkeys wordkeys.c
clean:
	@rm -f keywords wordkeys *.txt *.o
	@echo "Cleaning"

test : keywords
	@echo "Testing keywords with worst case"
	@time ./keywords $(num2)

wordkeys.o : 
	$(CC) -c wordkeys.c

keywords.o :
	$(CC) -c keywords.c

utilfuncs.o : 
	$(CC) -c utilfuncs.c
