#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class sudokuTriplet{
private:
	int level;
	int number;
	char character;
	bool upperCase = false;
	
public:
	sudokuTriplet(int l, int n, char c, bool u = false){
		level = l;
		number = n;
		character = c;
		upperCase = u;
	}
	int getLevel(){return level;}
	int getNumber(){return number;}
	char getChar(){return character;}
	bool isUpperCase(){return upperCase;}
	void setToUpperCase(){upperCase = true;}
};

vector<vector<char>> getKeyValues(string inputFile);
vector<vector<int>> getPuzzleValues(string inputFile);
string getCodedMesssage(vector<sudokuTriplet> v);
string decodeMessage(string inputFile, vector<vector<char>> v);
vector<sudokuTriplet> map(string key, string puzzle);
string getMessageFromFile(string fileName);
