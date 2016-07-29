#include "gtest/gtest.h"
#include "RSA.cpp"

TEST (Prime, isProbablyPrime)
{
    EXPECT_EQ(isProbablyPrime(961750679, 10), true);
    EXPECT_EQ(isProbablyPrime(977835239, 10), true);
    EXPECT_EQ(isProbablyPrime(295077091, 10), true);
    EXPECT_EQ(isProbablyPrime(314606869, 10), true);
    EXPECT_EQ(isProbablyPrime(104458129, 10), true);
    EXPECT_EQ(isProbablyPrime(961750681, 10), false);
    EXPECT_EQ(isProbablyPrime(977835241, 10), false);
    EXPECT_EQ(isProbablyPrime(295077093, 10), false);
    EXPECT_EQ(isProbablyPrime(314606871, 10), false);
    EXPECT_EQ(isProbablyPrime(104458131, 10), false);
}

TEST(Bits, numOfBits)
{
    EXPECT_EQ(numOfBits(1), 1);
    EXPECT_EQ(numOfBits(7), 3);
    EXPECT_EQ(numOfBits(8), 4);
    EXPECT_EQ(numOfBits(123), 7);
    EXPECT_EQ(numOfBits(431), 9);
    EXPECT_EQ(numOfBits(76324), 17);
    EXPECT_EQ(numOfBits(1094328), 21);
}

TEST(BinaryModulo, Modulo)
{
    EXPECT_EQ(modulo(10, 0, 5), 1);
    EXPECT_EQ(modulo(10, 1, 5), 0);
    EXPECT_EQ(modulo(10, 1, 15), 10);
    EXPECT_EQ(modulo(13, 2, 15), 4);
    EXPECT_EQ(modulo(43, 6, 1324), 517);
    EXPECT_EQ(modulo(34, 10, 783), 223);
}

TEST(GeneratePrime, LowerUpperLimits)
{
    EXPECT_EQ(numOfBits(generatePrime(16, 512)), 16);
    EXPECT_EQ(numOfBits(generatePrime(16, 512)), 512);
}

TEST(SquareRoot, Sqrt)
{
    EXPECT_EQ(getSqrt(25), 5);
    EXPECT_EQ(getSqrt(169), 13);
    EXPECT_EQ(getSqrt(54756), 234);
    EXPECT_EQ(getSqrt(2998219536), 54756);
    EXPECT_EQ(ceilingSqrt(27), 6);
    EXPECT_EQ(ceilingSqrt(172), 14);
    EXPECT_EQ(ceilingSqrt(54761), 235);
    EXPECT_EQ(ceilingSqrt(2998219537), 54757);
    EXPECT_EQ(isSquare(25), true);
    EXPECT_EQ(isSquare(72), false);
    EXPECT_EQ(isSquare(54761), false);
    EXPECT_EQ(isSquare(2998219536), true);
}

TEST(Fermat, Factorizaton) 
{
    EXPECT_EQ(fermatFactorization(221), 17);
    EXPECT_EQ(fermatFactorization(49644211), 7919);
    EXPECT_EQ(fermatFactorization(10925581581422743), 104655839);
}

TEST(CRT, calculateNthPower)
{
	EXPECT_EQ(cpp_int(0), calculateNthPower(0, 3));
	EXPECT_EQ(cpp_int(1), calculateNthPower(3, 0));
	EXPECT_EQ(cpp_int(125), calculateNthPower(5, 3));
	EXPECT_EQ(cpp_int(2097152), calculateNthPower(8, 7));
	EXPECT_EQ(cpp_int(2985984), calculateNthPower(12, 6));
}

TEST(CRT, calculateNthRoot)
{
	EXPECT_EQ(cpp_int(0), calculateNthRoot(0, 3));
	EXPECT_EQ(cpp_int(1), calculateNthRoot(1, 5));
	EXPECT_EQ(cpp_int(5), calculateNthRoot(125, 3));
	EXPECT_EQ(cpp_int(8), calculateNthRoot(2097152, 7));
	EXPECT_EQ(cpp_int(12), calculateNthRoot(2985984, 6));
}

TEST(CRT, testCRT)
{
	//EXPECT_EQ(testCRT(102, 3), 102);
	//EXPECT_EQ(testCRT(1645, 12), 1645);
}

int main(int argc, char * argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
