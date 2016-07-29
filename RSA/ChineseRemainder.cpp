#include "ChineseRemainder.h"

cpp_int calculateCRTCompnent(vector<cpp_int> N, vector<cpp_int> Ciphers, int n)
{
	cpp_int x = 1; //Stores the value N/n_i where N is the product of all n modulos

	//Calculate N/n_i
	for (int i = 0; i < N.size(); ++i) {

		if (i != n)
			x *= N[i];
	}

	//Calculates c_i * N/n_i * d, where d = x^-1 mod(n_i)
	return Ciphers[n] * x * generateD(x, N[n]);
}

cpp_int chineseRemainderTheorem(vector<cpp_int> N, vector<cpp_int> Ciphers, cpp_int e)
{

	cpp_int m = 0;

	//Add up each component of the CRT
	for (int i = 0; i < N.size(); ++i) {
		m += calculateCRTCompnent(N, Ciphers, i);
	}

	cpp_int n = 1;

	//Caculate N which is the product of all n modulos
	for (int i = 0; i < N.size(); ++i) {
		n *= N[i];
	}

	return calculateNthRoot(m%n, e);
}

//Computes the 'floor' Nth root
cpp_int calculateNthRoot(cpp_int N, cpp_int exp)
{
	//Special case
	if (N == 1)
		return 1;

	cpp_int guess = N / exp;

	for (cpp_int i = 0; i < cpp_int(numOfBits(N))*exp; ++i) {
		guess = ((exp-1)*guess + N / pow_cpp(guess,exp-1)) / exp;
	}

	return guess;
}

cpp_int setupCRT(cpp_int nmessages)
{
	cpp_int value;
	string response;
	vector<cpp_int> N;
	vector<cpp_int> Ciphers;


	//Store n modulos
	for (int i = 0; i < nmessages.ToInt(); ++i)
	{
		cout << "n modulo " << i + 1 << "- ";
		cin >> response;
		value.FromString(response.c_str());
		N.push_back(value);
	}

	//Store ciphers
	for (int i = 0; i < nmessages.ToInt(); ++i) {
		cout << "cipher " << i + 1 << "- ";
		cin >> response;
		value.FromString(response.c_str());
		Ciphers.push_back(value);
	}

	return chineseRemainderTheorem(N, Ciphers, nmessages);
}
