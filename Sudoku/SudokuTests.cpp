#include "gtest/gtest.h"
#include "SudokuLSB.h"

TEST(Sudoku, mapTest){
	vector<sudokuTriplet> m = map("Key.txt","Puzzle.txt");
	EXPECT_EQ(0, m[0].getLevel());
	EXPECT_EQ(2, m[0].getNumber());
	EXPECT_EQ('A', m[0].getChar());
	EXPECT_EQ(1, m[4].getLevel());
	EXPECT_EQ(1, m[4].getNumber());
	EXPECT_EQ('D', m[4].getChar());
	EXPECT_EQ(3, m[18].getLevel());
	EXPECT_EQ(8, m[18].getNumber());
	EXPECT_EQ('4', m[18].getChar());
}

TEST(Sudoku, getKeyValuesTest){
	vector<vector<char>> v1(9,vector<char>(9));
	vector<vector<char>> v2 = getKeyValues("Sudoku.sudoku");
	vector<vector<char>> v3 = getKeyValues("Sudoku2.sudoku");
	for(int i=0; i<v1.size(); ++i)
		for(int j=0; j<v1[i].size(); ++j){
			v1[i][j] = (j+1);
		}
	EXPECT_EQ(sameContentChar(v1,v2),false);
	EXPECT_EQ(sameContentChar(v1,v3),false);
	for(int i=0; i<v1.size(); ++i)
		for(int j=0; j<v1[i].size(); ++j){
			v1[i][j] = 9-j;
		}
	EXPECT_EQ(sameContentChar(v1,v3),false);

}

TEST(Sudoku, getPuzzleValuesTest){
	vector<vector<int>> v1(9,vector<int>(9));
	vector<vector<int>> v2 = getPuzzleValues("Sudoku.sudoku");
	vector<vector<int>> v3 = getPuzzleValues("Sudoku2.sudoku");
	for(int i=0; i<v1.size(); ++i)
		for(int j=0; j<v1[i].size(); ++j){
			v1[i][j] = j+1;
		}
	EXPECT_EQ(sameContentInt(v1,v2),true);
	EXPECT_EQ(sameContentInt(v1,v3),true);
	for(int i=0; i<v1.size(); ++i)
		for(int j=0; j<v1[i].size(); ++j){
			v1[i][j] = 9-j;
		}
	EXPECT_EQ(sameContentInt(v1,v3),false);
}

TEST(Sudoku, encodeMesssageTest){
	EXPECT_EQ("231140320320440",encodeMesssage("Key.txt","Sudoku.sudoku","Hello"));
	EXPECT_EQ("231140320320440120030",encodeMesssage("Key.txt","Sudoku.sudoku","Hello 1"));
	EXPECT_EQ("030160280380430560650710820",encodeMesssage("Key.txt","Sudoku.sudoku","123456789"));
	EXPECT_EQ("850231140320320440870621230140540140",encodeMesssage("Key.txt","Sudoku.sudoku","/Hello.There"));
}

TEST(Sudoku, decodeMessageTest){
	EXPECT_EQ("Hello",decodeMessage("Key.txt","Sudoku.sudoku","231140320320440"));
	EXPECT_EQ("Hello 1",decodeMessage("Key.txt","Sudoku.sudoku","231140320320440120030"));
	EXPECT_EQ("123456789",decodeMessage("Key.txt","Sudoku.sudoku","030160280380430560650710820"));
	EXPECT_EQ("/Hello.There",decodeMessage("Key.txt","Sudoku.sudoku","850231140320320440870621230140540140"));
}

TEST(Sudoku, getMessageFromFileTest){
	EXPECT_EQ("This is a message",getMessageFromFile("6.1.txt"));
	EXPECT_EQ("Thisisamessage",getMessageFromFile("6.2.txt"));
	EXPECT_EQ("This\ris\ra\rmessage",getMessageFromFile("6.3.txt"));
}





int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
