#ifndef PROJECT4_CRT_H
#define PROJECT4_CRT_H

#include "RSA.h"

cpp_int setupCRT(cpp_int nmessages);
cpp_int calculateNthRoot(cpp_int N, cpp_int exp);
cpp_int calculateCRTCompnent(vector<cpp_int> N, vector<cpp_int> Ciphers, int n);
cpp_int chineseRemainderTheorem(vector<cpp_int> N, vector<cpp_int> Ciphers, cpp_int e);

#endif //PROJECT4_CRT_H


