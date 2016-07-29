#ifndef PROJECT4_FERMAT_H
#define PROJECT4_FERMAT_H

#include <iostream>
#include "Prime.h"
#include "RSA.h"

bool isSquare(cpp_int N);
cpp_int floorSqrt(cpp_int N);
cpp_int ceilingSqrt(cpp_int N);
cpp_int fermatFactorization(cpp_int N);

#endif //PROJECT4_FERMAT_H
