#include "RSA.h"
//generates d.
cpp_int generateD(cpp_int e, cpp_int phi_n){
	vector<cpp_int> u;
	vector<cpp_int> v;
	cpp_int q, temp1, temp2, temp3;

	u.push_back(1); u.push_back(0); u.push_back(phi_n);
	v.push_back(0); v.push_back(1); v.push_back(e);

	while (v[2] != 0){
		q = u[2] / v[2];
		temp1 = u[0] - q * v[0];
		temp2 = u[1] - q * v[1];
		temp3 = u[2] - q * v[2];
		u[0] = v[0];
		u[1] = v[1];
		u[2] = v[2];
		v[0] = temp1;
		v[1] = temp2;
		v[2] = temp3;
	}
	if (u[1] < 0) return (u[1] + phi_n);
	else return (u[1]);
}

//generates e.
cpp_int generateE(cpp_int phi_n){
	bool check = false;
	cpp_int e, tempE;

	while (!check){
		e = generatePrime(16, 512);
		while (e > phi_n){
			//cout << "in loop:" << endl;
			e = generatePrime(15, 512);
		}
		tempE = EuAlgo(e, phi_n);
		if (tempE == 1 && e < phi_n){
			check = true;
		}
	}
	return e;
}

//Eucledian Algorithm to find GCD
cpp_int EuAlgo(cpp_int a, cpp_int b){
	cpp_int firstNum = a;
	cpp_int secondNum = b;
	cpp_int quotient;
	cpp_int remainder;

	// firstNum = seconNum*Quotient + Remainder
	while (secondNum != 0){
		quotient = (firstNum / secondNum);
		remainder = firstNum - (secondNum*quotient);
		firstNum = secondNum;
		secondNum = remainder;
	}
	return firstNum;
}

//convert cpp_int to string
string toString(cpp_int& bigNum){
	stringstream ss;
	ss << bigNum;
	return ss.str();
}

//basic character table, converts ASCII values into a range from 0-94
cpp_int b94(char& letter){
	return (126 - letter);
}
//converts from character table, to ASCII value.
char charI(int& num){
	return abs(num - 126);
}

//converts cpp_int to a char.
char b10(cpp_int& num){ 
	int temp = stoi(toString(num));
	return charI(temp);
}

//computes base10 from character values.
cpp_int base10(queue<char>& temp){
	queue<char> meh = temp;
	cpp_int size = temp.size() - 1;
	cpp_int base10 = 0;
	cpp_int holder;
	while (!meh.empty()){
		holder = meh.front() - 48;
		base10 += holder*pow_cpp(10, size);
		meh.pop();
		--size;
	}
	return base10;
}


//parses the input file, stores in a stack
bool encrypt(cpp_int& d, cpp_int& e, cpp_int& n){
	string line;
	char letter;
	cpp_int temp;
	stack<cpp_int> block;
	cpp_int expNum = exp(d);
	cout << "Block Size: " << expNum << endl;
	ofstream myfile("Cypher.txt");

	ifstream openfile("Message.txt");
	if (openfile.is_open()){
		while (getline(openfile, line)){
			stringstream parse(line);
			for (int i = 0; i < line.length(); ++i){
				parse >> noskipws >> letter;		
				temp = b94(letter);
				block.push(temp);				
			}
		}
		openfile.close();
	}
	else{
		cout << "Unable to open file";
		return false;
	}
	cypherBlock(e, n, myfile, block, expNum);
	myfile.close();
	return true;
}

//multiplies ASCII value by 95^i where i < x = log(n)/log(94) and applies key
void cypherBlock(cpp_int& e, cpp_int& n, ofstream& myfile, stack<cpp_int>& temp, cpp_int& tempExp){
	stack<cpp_int> block = temp;
	cpp_int size = block.size();
	cpp_int bigNum = 0;
	cpp_int counter = 0;
	cpp_int cypher;
	cpp_int expNum = tempExp;

	while(!block.empty()){
		bigNum += block.top()*(pow_cpp(95,counter));
		block.pop();		
		++counter;
		if (counter == expNum){
			cypher = modulo(bigNum, e, n);
			secretMsg(myfile, cypher, tempExp);
			counter = 0;
			bigNum = 0;
		}
	}
	if (block.empty() && (counter != 0 ) ){
		cypher = modulo(bigNum, e, n);
		secretMsg(myfile, cypher, tempExp);
	}
}

// converts the block into characters using the remainder
void secretMsg(ofstream& myfile, cpp_int& tempCypher, cpp_int& tempExp){
	stack<cpp_int> holder;
	cpp_int firstNum = tempCypher;
	cpp_int secondNum = 95;
	cpp_int expNum = tempExp;
	char letter;
	cpp_int quotient, remainder, size, temp;
	cpp_int diff = 0;
	cpp_int t = 1;

	// firstNum = seconNum*Quotient + Remainder
	while (t != 0){
		quotient = (firstNum / secondNum);
		t = (secondNum*quotient);
		remainder = firstNum - t;
		holder.push(remainder);
		firstNum = quotient;
	}
	size = holder.size();
	//adds padding to blocks 
	if (size < expNum + 1){
		diff = (expNum + 1) - size;
		for (cpp_int i = 0; i < diff; ++i){
			holder.push(0);
		}
	}
	while (!holder.empty()){
		temp = holder.top();
		letter = b10(temp);
		myfile << letter;
		holder.pop();
	}
}


//============Decryption============================
//reads keys from file
bool readKeys(cpp_int& tempD, cpp_int& tempN){
	string line;
	char letter;
	cpp_int temp;
	queue<char> d;
	queue<char> p;
	queue<char> q;
	int counter = 0;

	char ch;
	ifstream read("privateKey.txt");
	if (read.is_open()){
		while (read >> ch) {
			if (ch == '#'){
				++counter;
				read >> ch;
			}
			if (counter == 0){
				d.push(ch);
			}
			else if (counter == 1){
				p.push(ch);
			}
			else if (counter == 2){
				q.push(ch);
			}
		}
		read.close();
	}
	else{
		cout << "Unable to open file";
		return false;
	}
	tempD = base10(d); 
	tempN = base10(q)*base10(p);
	return true;
}

//computes n, calls readCypher and convert
bool decrypt(){
	cpp_int d = 0;
	cpp_int n = 0;
	stack<char> code;

	readKeys(d, n);
	cout <<endl << "Printing d and n.." << endl;
	cout <<"d :"<< d << endl << endl;
	cout <<"n :"<< n << endl;

	cpp_int expNum = exp(d) + 1;
	cout << "Block Size: " << expNum << endl << endl;

	cout << "Reading in Cypher.. from Cypher.txt" << endl;
	readCypher(code);

	cout << "Decoding Cyper.." << endl;
	convert(code, expNum, d, n);

	return false;
}

//reads encoded message from file
bool readCypher(stack<char>& code){
	string line;
	char ch;
	ifstream readCrypt("Cypher.txt");
	if (readCrypt.is_open()){
		while (readCrypt >>noskipws>> ch) {
			code.push(ch);
		}
		readCrypt.close();
	}
	else{
		cout << "Unable to open file";
		return false;
	}
	return true;
}

//splits encoded message into blocks and multiples by 95^i
bool convert(stack<char>& code, cpp_int& expNum, cpp_int& d, cpp_int& n){
	cpp_int counter = 0;
	cpp_int temp, cypher;
	cpp_int bigNum = 0;
	ofstream file("DecryptedMessage.txt");

	while (!code.empty()){
		temp = b94(code.top());
		bigNum += temp*(pow_cpp(95, counter ));
		++counter;
		code.pop();
		if (counter == expNum ){
			cypher = modulo(bigNum, d, n);
			decode(file, cypher, expNum);
			counter = 0;
			bigNum = 0;
		}	
	}
	if (code.empty() && (counter != 0)){
		cypher = modulo(bigNum, d, n);
		decode(file, cypher, expNum);
	}

	return true;
}

//decodes blocks of numbers using remainder
bool decode(ofstream& myfile, cpp_int& cypher, cpp_int& expNum){
	stack<cpp_int> holder;
	cpp_int firstNum = cypher;
	cpp_int secondNum = 95;
	char letter;
	cpp_int quotient, remainder, size, temp, t;

	// firstNum = seconNum*Quotient + Remainder
	while (t != 0){
		quotient = (firstNum / secondNum);
		t = (secondNum*quotient);
		remainder = firstNum - t;
		holder.push(remainder);
		firstNum = quotient;
	}
	while (!holder.empty()){
		temp = holder.top();
		letter = b10(temp);
		myfile << letter;
		holder.pop();
	}

	return true;
}
