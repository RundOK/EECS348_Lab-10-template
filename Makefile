CC := g++
CFLAGS := -Wall

calculator.exe: main.o calculator.o
	$(CC) $(CFLAGS) -o main.o calculator.o

main.o: main.cpp calculator.hpp
	$(CC) $(CFLAGS) -c main.cpp

calculator.o: calculator.cpp calculator.hpp
	$(CC) $(CFLAGS) -c calculator.cpp

