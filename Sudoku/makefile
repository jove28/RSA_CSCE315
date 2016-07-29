CC = g++
CFLAGS = -O3 -pipe

all: Sudoku

Sudoku: SudokuLSB.o SudokuSolver.o SudokuDestruction.o
	g++ -std=c++11 $(CFLAGS) SudokuLSB.o SudokuSolver.o SudokuDestruction.o -o Sudoku

SudokuLSB.o: SudokuLSB.h SudokuLSB.cpp
	g++ -std=c++11 -c SudokuLSB.cpp

SudokuSolver.o: SudokuSolver.h SudokuSolver.cpp
	g++ -std=c++11 -c SudokuSolver.cpp

SudokuDestruction.o: SudokuDestruction.h SudokuDestruction.cpp
	g++ -std=c++11 -c SudokuDestruction.cpp
	
clean:
	rm -f *.o
