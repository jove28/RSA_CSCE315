#include "Fermat.h"

using namespace std;

//Only correct if perfect square
bool isSquare(cpp_int N) {

    cpp_int x = floorSqrt(N);

    if ((x*x)==N)
        return true;
    else
        return false;
}

//Computes the 'floor' square root
cpp_int floorSqrt(cpp_int N) {

    cpp_int guess = N/2;

    for (int i = 0; i < numOfBits(N); ++i) {
        guess = (guess+N/guess)/2;
    }

    return guess;
}

//Computes the 'ceiling' square root
cpp_int ceilingSqrt(cpp_int N) {

    cpp_int x = floorSqrt(N);

    if ((x*x)==N)
        return x;
    else
        return x+1;
}

//Attempts to factor N into p and q, returns p
cpp_int fermatFactorization(cpp_int N) {

    cpp_int a = ceilingSqrt(N);
    cpp_int b = a*a - N; //a^2 - N = b^2

    //While not perfect square
    while (!isSquare(b)) {
        a += 1;
        b = a*a-N; //a^2 - N = b^2
    }

    return a + floorSqrt(b);

}
