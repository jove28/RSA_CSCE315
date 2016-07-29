#include <iostream>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <stack>
#include <queue>
#include <sstream>
#include <fstream>
#include "ttmath/ttmath.h"

typedef ttmath::Int<40> cpp_int;

using namespace std;

int numOfBits(cpp_int number);
cpp_int pow_cpp(cpp_int base, cpp_int exp);
cpp_int exp(cpp_int d);
cpp_int modulo(cpp_int base, cpp_int exp, cpp_int n);
bool isProbablyPrime(cpp_int n, int accuracy);
cpp_int generatePrime(int lower_limit, int upper_limit);
