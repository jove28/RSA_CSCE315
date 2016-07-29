//Created by Team: // No Comment
//For CSCE 315

#include "CSVsteganography.h"

//Checks two vectors to see if they have the same content
bool sameContent(vector <string> v1, vector <string> v2) {
	if (v1.size() != v2.size()) {
		return false;
	}
	for (int i = 0; i < v1.size(); ++i) {
		//cout << "Size. " << v1[i].size() << " vs " << v2[i].size() << "\n";
		//cout << "1. " << v1[i] << " vs " << v2[i] << "\n";
		if ( v1[i].compare(v2[i]) != 0 ) {
			return false;
		}
	}
	return true;
}
//Checks two vectors to see if they have the same content
bool sameContentInt(vector <int> v1, vector <int> v2) {
	if (v1.size() != v2.size()) {
		return false;
	}
	for (int i = 0; i < v1.size(); ++i) {
		//cout << "1. " << v1[i] << " vs " << v2[i] << "\n";
		if ( v1[i] != v2[i] ) {
			return false;
		}
	}
	return true;
}

//Extracts the cells from a string
vector<string> extractCells(string str) {
	int i = 0;
	bool inQuotes = false;
	vector <string> cells;
	string s;
	while (i < str.size()) {
		//Quote
		if ( str[i] == '\"') {
			//repeated quotes
			if ( (i+1) < str.size() && str[i+1] == '\"') {
				s += str[i];
				s += str[i+1];
				i++; //increment twice
			}
			else {
				s += str[i];
				inQuotes = !inQuotes;
			}
		}
		//Comma
		else if (!inQuotes && str[i] == ',') {
			cells.push_back(s);
			//cout << "Add: " << s << "\n";
			s = "";
		}
		//New Line
		else if (!inQuotes && str[i] == '\n') {
			cells.push_back(s);
			//cout << "Add: " << s << "\n";
			s = "";
		}
		else {
			s += str[i];
		}
		i++;
	}
	cells.push_back(s);
	//cout << "Add: " << s << "\n";
	return cells;
}

//Returns a vector of ints corresponding to # of spaces in "empty" cells
vector<int> detectSpaces(vector<string> v) {
	vector<int> ints;
	for (int i = 0; i < v.size(); ++i)	{
		for (int j = 0; j < v[i].size(); ) {
			if ( v[i][j] != ' ') {
				break;
			}
			j++;
			//If last character with only spaces
			if ( j == (v[i].size())) {
				ints.push_back( j-1 );
			}
		}
	}
	return ints;
}

//Removes spaces in "empty" cells
vector<string> deleteSpaces(vector<string> v) {
	vector<string> noSpaces;
	for (int i = 0; i < v.size(); ++i)	{
		for (int j = 0; j < v[i].size(); ) {
			if ( v[i][j] != ' ') {
				noSpaces.push_back( v[i] );
				break;
			}
			j++;
			//If just spaces
			if ( j == (v[i].size())) {
				noSpaces.push_back("");
			}
		}
	}
	return noSpaces;
}

//Converts vector of numbers into a string
string numbersToString(vector<int> v) {
	string s;
	for (int i = 0; (i+1) < v.size(); i+=2)	{
		string ch;
		char hex[2];
		sprintf(hex, "%x", v[i]);
		ch += hex;
		sprintf(hex, "%x", v[i+1]);
		ch += hex;
		//convert string of two hex::ints into decimal int
		unsigned int num = strtoul( ch.c_str(), NULL, 16 );
		char c = num;
		//cout << "Convert " << v[i] << " & " << v[i+1] << " to " << num << " = " << c << "\n";
		s += c;
	}
	return s;
}

//Converts message into vector of spaces
vector<string> createCells(string message) {
	stringstream stream;
	vector<string> cells;
	//convert to hex string
	for (int i = 0; i < message.size(); ++i) {
		char c = message[i];
		int num = c;
		stream << setfill ('0') << setw(2) << hex << num;
	}
	string hex = stream.str();
	//cout << hex << "\n";
	//create spaces corresponding to each number
	for (int i = 0; i < hex.size(); ++i) {
		string intStr;
		intStr += hex[i];
		int num = strtoul( intStr.c_str(), NULL, 16 );
		//cout << num;
		string s = string( (num+1), ' ');
		cells.push_back(s);
	}
	return cells;
}

//Converts cells to a string based on # of commas needed
string cellsToString(vector<string> v, int numberOfCommas, int blankLineBefore, bool beginningOfCSV) {
	//Check for valid # of commas
	if ( numberOfCommas < 0 ) {
		cout << "Cannot have negative commas!\n";
	}
	else if ( numberOfCommas == 0 ) {
		numberOfCommas = 5;
		beginningOfCSV = true;
	}
	int i = 0;
	string s;
	//Insert blank lines
	for (int k = 0; k < blankLineBefore; ++k) {
		if (!beginningOfCSV) {
			s+= "\n";
		}
		else {
			beginningOfCSV = false;
		}
		s+= string(numberOfCommas, ',');
	}
	//Split into columns and rows
	while (i < v.size()) {
		if (!beginningOfCSV) {
			s+= "\n";
		}
		else {
			beginningOfCSV = false;
		}
		//Split into rows
		for (int j = 0; j < numberOfCommas; ++j) {
			if (i < v.size()) {
				s+= v[i];
			}
			s+= ",";
			i++;
		}
		if (i < v.size()) {
			s+= v[i];
		}
		i++;
	}
	return s;
}

//Finds the number of commas = (#columns - 1)
int numberOfCommas (string str) {
	int i = 0;
	bool inQuotes = false;
	int number = 0;
	while (i < str.size()) {
		//Quote
		if ( str[i] == '\"') {
			//not repeated quotes
			if ( (i+1) < str.size() && str[i+1] == '\"' ) {}
			else {
				inQuotes = !inQuotes;
			}
		}
		//Comma
		else if (!inQuotes && str[i] == ',') {
			number++;
		}
		//New Line
		else if (!inQuotes && str[i] == '\n') {
			return number;
		}
		i++;
	}
	return number;
}