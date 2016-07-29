#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

bool sameContent(vector <string> v1, vector <string> v2);
bool sameContentInt(vector <int> v1, vector <int> v2);
vector<string> extractCells(string str);
vector<int> detectSpaces(vector<string> v);
vector<string> deleteSpaces(vector<string> v);
vector<string> createCells(string message);
string cellsToString(vector<string> v, int numberOfCommas, int blankLineBefore = 0, bool beginningOfCSV = false);
int numberOfCommas (string str);
string numbersToString(vector<int> v);