#include "gtest/gtest.h"
#include "CSVsteganography.h"

string image1Gray = "EasyBMPbackground.bmp";
string image2RGB = "EasyBMPbackground2.bmp";
string image1GrayModified = "output3.bmp";
string image2RGBModified = "output4.bmp";

TEST (findSpaces, result)
{
	vector<string> c1;
	c1.push_back(" ");
	vector<int> v1 = detectSpaces(c1);
	vector<int> a1;
	a1.push_back(0);
	EXPECT_EQ(sameContentInt(v1, a1), true);
	vector<string> c2;
	c2.push_back("                     ");
	vector<int> v2 = detectSpaces(c2);
	vector<int> a2;
	a2.push_back(20);
	EXPECT_EQ(sameContentInt(v2, a2), true);
	vector<string> c3;
	c3.push_back(" ");
	vector<int> v3 = detectSpaces(c3);
	vector<int> a3;
	a3.push_back(1);
	EXPECT_EQ(sameContentInt(v3, a3), false);

}

TEST (NullData, result)
{
	vector<string> c1;
	c1.push_back(" ");
	vector<string> v1 = deleteSpaces(c1);
	EXPECT_EQ(sameContent(v1, c1), false);
	vector<string> c2;
	c2.push_back("");
	EXPECT_EQ(sameContent(v1, c2), true);
	vector<string> c3;
	c3.push_back(" ");
	c3.push_back("    ");
	c3.push_back("  ");
	vector<string> v3 = deleteSpaces(c3);
	EXPECT_EQ(sameContent(v3, c3), false);
	vector<string> c4;
	c4.push_back("");
	c4.push_back("");
	c4.push_back("");
	EXPECT_EQ(sameContent(v3, c4), true);
	vector<string> c5;
	c5.push_back("a");
	vector<string> v5 = deleteSpaces(c5);
	EXPECT_EQ(sameContent(v5, c5), true);
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
