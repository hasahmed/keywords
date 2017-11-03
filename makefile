CC= g++
OBJS = keywords.o utilfuncs.o
CFLAGS = -std=c++14 -Wall

num1 = 538-8823
num2 = 999-9982

keywords: $(OBJS)
	$(CC) -o keywords $(OBJS) $(CFLAGS)

wordkeys : wordkeys.o
	$(CC) -o wordkeys wordkeys.c
clean:
	@rm -f keywords wordkeys *.o
	@echo "Cleaning"

test : keywords
	@echo "Testing keywords"
	@time ./keywords $(num2)

wordkeys.o : wordkeys.c
	$(CC) -c $(CFLAGS) wordkeys.c

keywords.o : keywords.cpp
	$(CC) -c $(CFLAGS) keywords.cpp

utilfuncs.o : utilfuncs.cpp utilfuncs.hpp
	$(CC) -c $(CFLAGS) utilfuncs.cpp
