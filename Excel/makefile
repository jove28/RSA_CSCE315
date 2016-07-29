CC = g++
CFLAGS = -O3 -pipe

all: munchkinexcel glinda

munchkinexcel: CSVsteganography.o munchkinexcel.o
	g++ -std=c++11 $(CFLAGS) CSVsteganography.o munchkinexcel.o -o munchkinexcel

glinda: CSVsteganography.o glinda.o
	g++ -std=c++11 $(CFLAGS) CSVsteganography.o glinda.o -o glinda
	
munchkinexcel.o: CSVsteganography.h munchkinexcel.cpp
	g++ -std=c++11 -c munchkinexcel.cpp

glinda.o: CSVsteganography.h glinda.cpp
	g++ -std=c++11 -c glinda.cpp

test: munchkinexcelTest glindaTest

munchkinexcelTest: CSVsteganography.h CSVTests.cpp
	g++ -std=c++11 -isystem gtest/include -pthread CSVsteganography.cpp CSVTests.cpp libgtest.a -o munchkinexcelTest

glindaTest: CSVsteganography.h CSVAttackTests.cpp
	g++ -std=c++11 -isystem gtest/include -pthread CSVsteganography.cpp CSVAttackTests.cpp libgtest.a -o glindaTest

CSVsteganography.o: CSVsteganography.h CSVsteganography.cpp 
	g++ -std=c++11 -c CSVsteganography.cpp 
	
clean:
	rm -f *.o
