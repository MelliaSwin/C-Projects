# Make file for pointers assignment

OBJS	= main.o shopping_cart.o store.o
CC		= g++
CCFLAGS	= -Wall -Wextra -pedantic -std=c++11 -g

all: reading_test shopping_test main 


main: $(OBJS)
	@echo "Compiling shopping_prog"
	$(CC) $(CCFLAGS) -o shopping_prog $(OBJS)
	
shopping_test: shopping_test.o shopping_cart.o
	@echo "Compiling Shopping Test"
	$(CC) $(CCFLAGS) -o shopping_test shopping_test.o shopping_cart.o
	
reading_test: reading_test.o shopping_cart.o store.o
	@echo "Compiling Reading Test"
	$(CC) $(CCFLAGS) -o reading_test reading_test.o shopping_cart.o store.o
	
store.o:
	@echo "Compiling store.cpp"
	$(CC) $(CCFLAGS) -c store.cpp

shopping_cart.o:
	@echo "Compiling shopping_cart.cpp"
	$(CC) $(CCFLAGS) -c shopping_cart.cpp
	
main.o:
	@echo "Compiling main.cpp"
	$(CC) $(CCFLAGS) -c main_files/main.cpp
	
reading_test.o:
	@echo "Compiling reading_test.cpp"
	$(CC) $(CCFLAGS) -c main_files/reading_test.cpp
	
shopping_test.o:
	@echo "Compiling shopping_test.cpp"
	$(CC) $(CCFLAGS) -c main_files/shopping_test.cpp


# -----
# clean by removing object files.

clean:
	rm $(OBJS) reading_test.o shopping_test.o 
	rm reading_test
	rm shopping_test
	rm shopping_prog
