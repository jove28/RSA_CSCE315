#include "RSA.h"

int main(){
	char currentChoice = '0';
	cout << "\nTo Encrypt:\n* message -> Message.txt\n"
		<< "To Decrypt:\n* cypher -> Cypher.txt\n* public key -> publicKey.txt\n";
	cout << "\nWhat do you want to do?\n1 - Encrypt\n2 - Decrypt\n3 - Exit\n > ";
	cout.flush();

	while (cin >> currentChoice){
		if (currentChoice == '1'){
			cout << "Calculating Public and Private Keys..." << endl;
			srand((unsigned int)time(NULL));
			// generating primes
			cpp_int p = generatePrime(16, 512); //281
			cpp_int q = generatePrime(16, 512); //167
			//n = pq
			cpp_int n = p * q;
			// φ(n) = (p − 1)(q − 1)
			cpp_int phi_n = (p - 1) * (q - 1);
			// generating e such that 1 < e < φ(n) ❛and φ(n) are co-prime
			cpp_int e = generateE(phi_n);  //39423
			cpp_int d = generateD(e, phi_n);  //26767
			
			ofstream publicKey("publicKey.txt");
			publicKey << n << endl << endl;
			publicKey << e << endl << endl;
			publicKey.close();
			
			ofstream privateKey("privateKey.txt");
			privateKey << d <<"#" << endl << endl;
			privateKey << p <<"#" <<endl << endl;
			privateKey << q <<"#"<< endl << endl;
			privateKey.close();

			cout << endl << "Encrypting file.." << endl << endl;
			encrypt(d, e, n);
			cout << "File encrypted to Cypher.txt, publicKey.txt, and privateKey.txt" << endl;
			return 1; 
		}
		else if (currentChoice == '2'){
			cout << endl << "Decrypting file.." << endl << endl;
			decrypt();
			cout << endl<< "File Decrypted to DecryptedMessage.txt\n\n" << endl;
			return 1; 
		}
		else if (currentChoice == '3'){
			return 1; 
		}
		else{
			cout << endl << "Not a valid choice, Try again" << endl;
		}
		cout << "\n\nWhat do you want to do?\n1 - Embed\n2 - Decrypt\n > ";
	}	
}