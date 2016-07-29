#include <iostream>
#include <array>
#include <string>
using namespace std;
pair<bool, array<int, 81>> solve(const char* in);
bool puzzle_solved(const char* in);
void sudokuToFile(string filename, pair<bool, array<int, 81>> p);
