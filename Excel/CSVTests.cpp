#include "gtest/gtest.h"
#include "CSVsteganography.h"
#include <iostream>
#include <fstream>
#include <vector>

//String to vector of strings
TEST(ExtractCells, sameVector) {
	string s1 = "a";
	vector<string> v1;
	v1.push_back(s1);
	EXPECT_EQ(sameContent(extractCells(s1), v1), true);

	string s2 = "\"\"\"a\"\"\"";
	vector<string> v2;
	v2.push_back(s2);
	EXPECT_EQ(sameContent(extractCells(s2), v2), true);

	string s3 = "\",\"";
	vector<string> v3;
	v3.push_back(s3);
	EXPECT_EQ(sameContent(extractCells(s3), v3), true);

	string s4 = "\n";
	vector<string> v4;
	v4.push_back("");
	v4.push_back("");
	EXPECT_EQ(sameContent(extractCells(s4), v4), true);
	EXPECT_EQ(sameContent(extractCells(s4), v3), false);
}

//Return vector of # of spaces in "empty" cells
TEST(countSpaces, result) {
	string s1 = " ";
	vector<int> v1;
	v1.push_back(0);
	EXPECT_EQ(sameContentInt(detectSpaces(extractCells(s1)), v1), true);

	string s2 = " ,  ";
	vector<int> v2;
	v2.push_back(0);
	v2.push_back(1);
	EXPECT_EQ(sameContentInt(detectSpaces(extractCells(s2)), v2), true);
}

//Turns a string into a vector of ints
TEST(toVectorInt, result) {
	vector<string> v1;
	v1.push_back(string(7, ' '));
	v1.push_back(string(2, ' '));
	EXPECT_EQ(sameContent(createCells("a"), v1), true);
	
}

TEST(CSVsteganography, numberOfCommasTest){
	EXPECT_EQ(numberOfCommas(",,,"),3);
	EXPECT_EQ(numberOfCommas(",,,ajjfka"),3);
	EXPECT_EQ(numberOfCommas(""),0);
	EXPECT_EQ(numberOfCommas("kdlsak"),0);
	EXPECT_EQ(numberOfCommas("aldkkdja,,,"),3);
	
}

TEST(CSVsteganography, cellsToStringTest){
	/*vector<string> test1 = {};
	EXPECT_EQ(cellsToString(),);*/
}

TEST(CSVsteganography, numbersToStringTest){
	vector<int> test1 = {1};
	vector<int> test2 = {1,1,1,1,1,1,1,1,1,1,1,1,1};
	vector<int> test3 = {1,2,3};
	vector<int> test4 = {};
	EXPECT_EQ(numbersToString(test1),"");
	EXPECT_EQ(numbersToString(test2),"\x11\x11\x11\x11\x11\x11");
	EXPECT_EQ(numbersToString(test3),"\x12");
	EXPECT_EQ(numbersToString(test4),"");
}
int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
