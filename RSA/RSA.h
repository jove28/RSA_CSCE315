#include "Prime.h"

cpp_int generateD(cpp_int e, cpp_int phi_n);
cpp_int generateE(cpp_int phi_n);
cpp_int EuAlgo(cpp_int a, cpp_int b);
string toString(cpp_int& bigNum);
cpp_int b94(char& letter);
char charI(int& num);
char b10(cpp_int& num);
cpp_int base10(queue<char>& temp);

// encryption

bool encrypt(cpp_int& d, cpp_int& e, cpp_int& n);
void cypherBlock(cpp_int& e, cpp_int& n, ofstream& myfile,
	stack<cpp_int>& temp, cpp_int& exp);
void secretMsg(ofstream& myfile, cpp_int& tempCypher, cpp_int& exp);

//decryption
bool decrypt();
bool readKeys(cpp_int& d, cpp_int& n);
bool readCypher(stack<char>& code);
bool convert(stack<char>& code, cpp_int& expNum, cpp_int& d, cpp_int& n);
bool decode(ofstream& myfile, cpp_int& cypher, cpp_int& tempExp);
