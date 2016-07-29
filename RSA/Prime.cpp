#include "Prime.h"

//Current size of interger
int numOfBits(cpp_int number) {
	int bits = 1;
	while (number>1) {
		number /= 2;
		++bits;
	}
	return bits;
}

//base^exp
cpp_int pow_cpp(cpp_int N, cpp_int exp) {
	if (exp == 0) {
		return 1;
	}
	else if (exp == 1) {
		return N;
	}
	else if (exp % 2 == 0) {
		return pow_cpp(N*N, exp / 2);
	}
	else {
		return N*pow_cpp(N*N, (exp - 1) / 2);
	}
}

//compute the block size used to read in characters based on d 
cpp_int exp(cpp_int d) {
	cpp_int base = 95;  // 995 since I use ASCII values 32-126 which then convert to 0 -94
	cpp_int result = base;
	for (cpp_int i = 1; i < d; ++i) {
		result *= base;
		if (result > d){
			return i;
		}
	}
	return -1;
}

//base^exp mod n
cpp_int modulo(cpp_int base, cpp_int exp, cpp_int n) {
	cpp_int result = 1;
	base = base % n;

	//The value exp is represented in binary
	while (exp > 0) {
		//If the least sig bit of exp is 1
		if (exp % 2 == 1) {
			result = (result*base) % n;
			exp -= 1;
		}
		//Shift the least sig bit of exp out
		exp /= 2;
		//Square the base and % it
		base = (base*base) % n;
	}

	return result;
}

//Based on Miller-Rabin
bool isProbablyPrime(cpp_int n, int accuracy) {
	//Check if even number
	if (n % 2 == 0) {
		return false;
	}
	int s = 0;
	cpp_int d = 0;
	cpp_int temp = n - 1; //Used to determine s and d
	//Breakdown into s and d
	while (true) {
		if (temp % 2 == 0) {
			temp /= 2;
			++s;
		}
		else {
			d = temp;
			break;
		}
	}
	bool possible = false;
	for (int i = 0; i < accuracy; i++) {
		//Random from 2 to n-2
		cpp_int a = cpp_int(rand()) % (n - 2) + 2;
		//Compute x = a^(d*2^j) % n
		cpp_int x = modulo(a, d, n);
		//Opening case
		if (x == 1 || x == (n - 1)) {
			possible = true; //Possibly a prime
		}
		else {
			for (int j = 1; j <= s - 1; j++) {
				//Next case
				x = modulo(x, 2, n);
				if (x == 1) {
					return false; //The number is a composite
				}
				else if (x == (n - 1)) {
					possible = true; //Possibly a prime
					j = s - 1;
				}
			}
		}
		//The number is a composite
		if (!possible) {
			return false;
		}
	}
	return true;
}

//Generate a prime number within given bounds
cpp_int generatePrime(int lower_limit, int upper_limit) {
	int random;
	cpp_int result = 0;
	while (true) {

		//Number of bits
		if(upper_limit!=lower_limit) {
			random = rand() % (upper_limit - lower_limit) + lower_limit;
		} else {
			random = upper_limit;
		}

		//Generate random number
		for (int i = 0; i < random; ++i)
		{
			if(rand()%2 == 1 || (i+1  == random))
				result += pow_cpp(2, i);
		}


		//Check upper and lower bounds
		while (lower_limit <= numOfBits(result) && numOfBits(result) <= upper_limit) {
			//Check if result is even. If so, make it odd.
			if (result % 2 == 0) {
				result += 1;
			}
			//Keep checking odds until prime is found
			if (isProbablyPrime(result, 10)) {
				return result;
			}
			else {
				result += rand() % 999;
			}
		}
	}
	return -1;
}
