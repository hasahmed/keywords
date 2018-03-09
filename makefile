CC= gcc
#CFLAGS = -c -std=c11 -Wall -g
#LDFLAGS =

num1 = 538-8823
num2 = 999-9982
num3 = 267-7464



OBJS = keywords.o utilfuncs.o stringset.o strll.o

keywords: $(OBJS)
	$(CC) -o keywords $(OBJS) $(CFLAGS)

wordkeys : wordkeys.o
	$(CC) -o wordkeys wordkeys.c
clean:
	@rm -f keywords wordkeys *.o
	@echo "Cleaning"

test1 : keywords
	@echo "Testing keywords with $(num1)"
	@time ./keywords $(num1)

test2: keywords
	@echo "Testing keywords with $(num2)"
	@time ./keywords $(num2)

test3: keywords
	@echo "Testing keywords with $(num3)"
	@time ./keywords $(num3)

#wordkeys.o : wordkeys.c
	#$(CC) -c $(CFLAGS) wordkeys.c

#keywords.o : keywords.c
	#$(CC) -c $(CFLAGS) keywords.c

#utilfuncs.o : utilfuncs.c
	#$(CC) -c $(CFLAGS) utilfuncs.c
