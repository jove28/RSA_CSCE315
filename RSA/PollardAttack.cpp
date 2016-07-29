//Low Public Exponent Attack (Weiner's Theorem)
#include "PollardAttack.h"

/*int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}*/

cpp_int factorial(cpp_int f) {
	if (f == 1) {
		return 1;
	}
	return factorial(f-1)*f;
}

cpp_int pollardAttack(cpp_int N) {
	cpp_int a, p, k, r;
	while(true) {
		a = cpp_int(rand()) % N;
		p = EuAlgo(a, N);
		if ( p > 1 && p < N) {
			return p;
		}
		for(cpp_int i = 2; ; i++) {
			k = factorial(i);
			r = modulo(a, k, N);
			p = EuAlgo(r-1, N);
			if (p >= N) {
				break;
			}
			else if (p > 1) {
				return p;
			}
		}
	}
}

bool pollard_check(cpp_int N) {
	cpp_int p = pollardAttack(N);
	if(N % p == 0)
		return true;
	else
		return false;
}

/*TEST(gtest, test91){
//checks if N is divisible by the result of pollard's factorization
	EXPECT_EQ(true, pollard_check(540143));
}

TEST(gtest, test92){
//checks if N is divisible by the result of pollard's factorization
	EXPECT_EQ(true, pollard_check(491389));
}

TEST(gtest, test94){
//checks if N is divisible by the result of pollard's factorization
	EXPECT_EQ(true, pollard_check(18923));
}

TEST(gtest, test95){
//checks if N is divisible by the result of pollard's factorization
	EXPECT_EQ(true, pollard_check(115147));
}

//This test takes too long; need to find a proper bound for the pollard funciton
TEST(gtest, test93){
//checks if N is divisible by the result of pollard's factorization
	srand((unsigned int)time(NULL));
	cpp_int p = generatePrime(16, 512);
	cpp_int q = generatePrime(16, 512);
	//n = pq
	cpp_int n = p * q;
	EXPECT_EQ(true, pollard_check(n));
}*/
