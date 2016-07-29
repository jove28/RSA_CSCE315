#include "SudokuLSB.h"
#include "SudokuSolver.h"

vector<sudokuTriplet> map(string k, string p){
	vector<sudokuTriplet> v;
	vector<vector<char>> key;
	vector<vector<int>> puzzle;
	key = getKeyValues(k);
	puzzle = getPuzzleValues(p);
	for(int i=0; i<9; ++i)
		for(int j=0; j<9; ++j){
			if(key[i][j] != '*'){
				if(key[i][j] == '_'){
					sudokuTriplet sT(i, puzzle[i][j],' ');
					v.push_back(sT);
				}
				else{
					sudokuTriplet sT(i, puzzle[i][j],key[i][j]);
					v.push_back(sT);
				}
			}
		}
	return v;
}

vector<vector<char>> getKeyValues(string inputFile){
	vector<vector<char>> key(9,vector<char>(9));
	ifstream in;
	in.open(inputFile);
	for(int i=0; i<9; ++i)
		for(int j=0; j<9; ++j)
			in >> key[i][j];
	in.close();
	return key;	
}

vector<vector<int>> getPuzzleValues(string inputFile){
	vector<vector<int>> puzzle(9,vector<int>(9));
	ifstream in;
	in.open(inputFile);
	for(int i=0; i<9; ++i)
		for(int j=0; j<9; ++j)
			in >> puzzle[i][j];
	in.close();
	return puzzle;
}

string encodeMesssage(string key, string puzzle){
	string message;
	string encodedMessage = "";
	vector<sudokuTriplet> sT = map(key,puzzle);
	cout<<"Message to Encode:"<<endl;
	cin.ignore();
	getline(cin,message);
	cout<<"Encoding Message: "<<message<<endl;
	for(int i=0; i<message.size(); ++i){
		for(int j=0; j<sT.size(); ++j){
			if(tolower(message[i]) == tolower(sT[j].getChar())){
				if(isupper(message[i]))
					encodedMessage+= to_string(sT[j].getLevel()) + to_string(sT[j].getNumber()) + '1';
				else encodedMessage+= to_string(sT[j].getLevel()) + to_string(sT[j].getNumber()) + '0';
			}
		}
	}
	ofstream out;
	out.open("Coded Message.txt");
	out << encodedMessage;
	out.close();
	cout<<"Coded Message is in file Coded Message.txt"<<endl;
	return encodedMessage;
}

string decodeMessage(string k, string p, string message){
	vector<vector<char>> key = getKeyValues(k);;
	vector<vector<int>> puzzle = getPuzzleValues(p);
	vector<sudokuTriplet> sT = map(k,p);
	string answer = "";
	int level;
	int number;
	bool isUpperCase;
	for(int i=0; i<message.size()/3; ++i){
		level = message[3*i] - '0';
		number = message[3*i+1] - '0';
		isUpperCase = message[3*i+2] - '0';
		for(int j=0; j<sT.size(); ++j){
			if(sT[j].getLevel() == level && sT[j].getNumber() == number){
				if(sT[j].getChar() == '_')
					answer += " ";
				else if(!isUpperCase)
					answer += tolower(sT[j].getChar());
				else answer += sT[j].getChar();
			}
		}
	}
	return answer;
}

string getMessageFromFile(string inputFile){
	string s = "";
	string temp;
	ifstream in;
	in.open(inputFile);
	while(!in.eof()){
		getline(in,temp);
		s += temp;
	}
	in.close();
	return s;
}

int main(){
	string puzzle;
	string key;
	string response;
	string message;
	string retry = "n";
	bool again = true;
	while(again){
		cout << "Please enter your sudoku puzzle (eg. 1234...)\n > ";
		cin >> puzzle;
		cout<<"Please enter the name of the file with the key\n > ";
		cin >> key;
		pair<bool, array<int, 81>> pair = solve(puzzle.c_str());
		sudokuToFile("Sudoku.sudoku",pair);
		cout<<"What do you want to do?\n1 - Encode\n2 - Decode\n > ";
		cin >> response;
		while(true){
			if(response == "1" || response == "2")
				break;
			else{
				cout<<"Sorry wrong input"<<endl <<"What do you want to do?\n1 - Encode\n2 - Decode\n > ";
				cin >> response;
			}
		}
		if(response == "1"){
			encodeMesssage(key, "Sudoku2.sudoku");
		}
		if(response == "2"){
			cout<<"What is the filename with your message?\n > ";
			cin.ignore();
			getline(cin,message);
			cout<<"Decoding Message from "<<message<<endl;
			cout<<"The message is:"<<endl<<decodeMessage(key,"Sudoku2.sudoku",getMessageFromFile(message))<<endl;
		}
		cout<<"\nWould you like to do another? (y/n)\n > ";
		cin >> retry;
		if(retry == "Y" || retry == "y")
			again = true;
		else again = false;
	}
}
