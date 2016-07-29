#include "ChineseRemainder.h"
#include "PollardAttack.h"
#include "Fermat.h"


void setup() {
	
	string response;

	cout << "p: ";
	cin >> response;
	cpp_int p = atoi(response.c_str());

	cout << "q: ";
	cin >> response;
	cpp_int q = atoi(response.c_str());
	
	cout << "e: ";
	cin >> response;
	cpp_int e = atoi(response.c_str());
	

	/*cpp_int p = generatePrime(16, 16);
	cpp_int q = generatePrime(16, 16);*/

	cpp_int n = p * q;
	cpp_int phi_n = (p - 1) * (q - 1);
	//cpp_int e = generateE(phi_n);
	cpp_int d = generateD(e, phi_n);

	ofstream publicKey("publicKey.txt");
	publicKey << n << endl << endl;
	publicKey << e << endl << endl;
	publicKey.close();

	encrypt(d, e, n);
}

int main() {

	srand(static_cast<unsigned int>(time(nullptr)));

	string response;
	cout << "Run encryption setup? (Y/N)\n" << endl;
	cin >> response;

	if (response=="Y") {
		setup();
	}

    cout << "\nWhich test do you want to run?\n1 - Fermat Factorization\n2 - Pollard p-1\n3 - ChineseRemainderTheorem\n > ";
    cin >> response;

	ifstream input("publicKey.txt");

	cpp_int n;
	cpp_int e;

	input >> n;
	input >> e;

    int value = atoi(response.c_str());

	int nmessages; //number of messages (CRT)
	cpp_int nq; //factored q
	cpp_int np; //factored p
	cpp_int message; //message from CRT

    switch (value) {
        case 1:
			nq = fermatFactorization(n);
			np = n / nq;
            break;
        case 2:
            nq = pollardAttack(n);
			np = n / nq;
            break;
        case 3:
			cout << "\n Numbers of messages: ";
			cin >> response;
			nmessages = atoi(response.c_str());
            message = setupCRT(nmessages);
            break;
        default:
            cout << "Invalid choice" << endl;
            return -1;
    }

	//Fermat or Pollard
	if (value == 1 || value == 2) {

		cpp_int totient = (np - 1)*(nq - 1);
		cpp_int d = generateD(e, totient);

		ofstream privateKey("privateKey.txt");
		privateKey << d << "#" << endl << endl;
		privateKey << np << "#" << endl << endl;
		privateKey << nq << "#" << endl << endl;
		privateKey.close();

		decrypt();

	} else { //Chinese Remainder
		ofstream decrypt("DecryptedMessage.txt");
		decrypt << message << endl;
	}
}
