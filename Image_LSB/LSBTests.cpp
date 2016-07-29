#include "gtest/gtest.h"
#include "steganography.h"
#include "EasyBMP.h"
#include <iostream>
#include <fstream>

/*#include "PSNR.h"
TEST(PSNR, MSETest){
	BMP LenaB;
	LenaB.ReadFromFile("lenaB.bmp");
	BMP LenaB11;
	LenaB11.ReadFromFile("LenaB11.bmp");
	BMP LenaB12;
	LenaB12.ReadFromFile("LenaB12.bmp");
	BMP LenaB21;
	LenaB21.ReadFromFile("LenaB21.bmp");
	BMP LenaB22;
	LenaB22.ReadFromFile("LenaB22.bmp");
	BMP LenaC;
	LenaC.ReadFromFile("lenaC.bmp");
	BMP LenaC11;
	LenaC11.ReadFromFile("LenaC11.bmp");
	BMP LenaC12;
	LenaC12.ReadFromFile("LenaC12.bmp");
	BMP LenaC21;
	LenaC21.ReadFromFile("LenaC21.bmp");
	BMP LenaC22;
	LenaC22.ReadFromFile("LenaC22.bmp");
	
	ASSERT_DOUBLE_EQ(0, checkMSE(LenaB, LenaB));
	ASSERT_DOUBLE_EQ(0.000583648681640625, checkMSE(LenaB, LenaB11));
	ASSERT_DOUBLE_EQ(0.00020599365234375, checkMSE(LenaB, LenaB12));
	ASSERT_DOUBLE_EQ(0.0014801025390625, checkMSE(LenaB, LenaB21));
	ASSERT_DOUBLE_EQ(0.0005035400390625, checkMSE(LenaB, LenaB22));
	ASSERT_DOUBLE_EQ(0, checkMSE(LenaC, LenaC));
	ASSERT_DOUBLE_EQ(1644.6202545166016, checkMSE(LenaC, LenaC11));
	ASSERT_DOUBLE_EQ(0.00020599365234375, checkMSE(LenaC, LenaC12));
	ASSERT_DOUBLE_EQ(1644.6210784912109, checkMSE(LenaC, LenaC21));
	ASSERT_DOUBLE_EQ(0.00047810872395833332, checkMSE(LenaC, LenaC22));
}

TEST(PSNR, PSNRTest){
	BMP LenaB;
	LenaB.ReadFromFile("lenaB.bmp");
	BMP LenaB11;
	LenaB11.ReadFromFile("LenaB11.bmp");
	BMP LenaB12;
	LenaB12.ReadFromFile("LenaB12.bmp");
	BMP LenaB21;
	LenaB21.ReadFromFile("LenaB21.bmp");
	BMP LenaB22;
	LenaB22.ReadFromFile("LenaB22.bmp");
	BMP LenaC;
	LenaC.ReadFromFile("lenaC.bmp");
	BMP LenaC11;
	LenaC11.ReadFromFile("LenaC11.bmp");
	BMP LenaC12;
	LenaC12.ReadFromFile("LenaC12.bmp");
	BMP LenaC21;
	LenaC21.ReadFromFile("LenaC21.bmp");
	BMP LenaC22;
	LenaC22.ReadFromFile("LenaC22.bmp");
	
	ASSERT_DOUBLE_EQ(0, checkPSNR(LenaB, LenaB));
	ASSERT_DOUBLE_EQ(90.011713614412983, checkPSNR(LenaB, LenaB11));
	ASSERT_DOUBLE_EQ(94.534690324359275, checkPSNR(LenaB, LenaB12));
	ASSERT_DOUBLE_EQ(85.970310666646895, checkPSNR(LenaB, LenaB21));
	ASSERT_DOUBLE_EQ(90.652888610530468, checkPSNR(LenaB, LenaB22));
	ASSERT_DOUBLE_EQ(0, checkPSNR(LenaC, LenaC));
	ASSERT_DOUBLE_EQ(25.512572357457458, checkPSNR(LenaC, LenaC11));
	ASSERT_DOUBLE_EQ(94.534690324359275, checkPSNR(LenaC, LenaC12));
	ASSERT_DOUBLE_EQ(25.512570181590199, checkPSNR(LenaC, LenaC21));
	ASSERT_DOUBLE_EQ(90.877962020508988, checkPSNR(LenaC, LenaC22));
}*/

TEST(Steganography, getBitTest){
	ASSERT_STREQ("0",getBit(0,0).c_str());
	ASSERT_STREQ("0",getBit(0,10).c_str());
	ASSERT_STREQ("0",getBit(0,100).c_str());
	ASSERT_STREQ("1",getBit(0,155).c_str());
	ASSERT_STREQ("1",getBit(0,255).c_str());
	ASSERT_STREQ("0",getBit(1,0).c_str());
	ASSERT_STREQ("1",getBit(1,10).c_str());
	ASSERT_STREQ("0",getBit(1,100).c_str());
	ASSERT_STREQ("1",getBit(1,155).c_str());
	ASSERT_STREQ("1",getBit(1,255).c_str());
}

TEST(Steganography, setBitTest){
	ASSERT_EQ(100,setBit(0,'0',100));
	ASSERT_EQ(101,setBit(0,'1',100));
	ASSERT_EQ(100,setBit(1,'0',100));
	ASSERT_EQ(102,setBit(1,'1',100));
	ASSERT_EQ(0,setBit(0,'0',0));
	ASSERT_EQ(1,setBit(0,'1',0));
	ASSERT_EQ(0,setBit(1,'0',0));
	ASSERT_EQ(2,setBit(1,'1',0));
	ASSERT_EQ(254,setBit(0,'0',255));
	ASSERT_EQ(255,setBit(0,'1',255));
	ASSERT_EQ(253,setBit(1,'0',255));
	ASSERT_EQ(255,setBit(1,'1',255));
	
}

TEST(Steganography, addBinaryHeaderTest){
	ASSERT_STREQ("00000000000000000011010100000000test1",addBinaryHeader("test1","file1").c_str());
	ASSERT_STREQ("00000000011000100110110101110000000000000011010100000000test1",addBinaryHeader("test1","file1.bmp").c_str());
	ASSERT_STREQ("00000000011101000111100001110100000000000011010100000000test1",addBinaryHeader("test1","file1.txt").c_str());
	ASSERT_STREQ("00000000011100000110111001100111000000000011010100000000test1",addBinaryHeader("test1","file1.png").c_str());
	ASSERT_STREQ("00000000011110100110100101110000000000000011010100000000test1",addBinaryHeader("test1","file1.zip").c_str());
	ASSERT_STREQ("00000000000000000011010100000000test2",addBinaryHeader("test2","file2").c_str());
	ASSERT_STREQ("00000000011000100110110101110000000000000011010100000000test2",addBinaryHeader("test2","file2.bmp").c_str());
	ASSERT_STREQ("00000000011101000111100001110100000000000011010100000000test2",addBinaryHeader("test2","file2.txt").c_str());
	ASSERT_STREQ("00000000011100000110111001100111000000000011010100000000test2",addBinaryHeader("test2","file2.png").c_str());
	ASSERT_STREQ("00000000011110100110100101110000000000000011010100000000test2",addBinaryHeader("test2","file2.zip").c_str());
 }
 
 TEST(Steganography, writeMessageTest){
	BMP Lena;
	Lena.ReadFromFile("lena.bmp");
	BMP LenaFail;
	ASSERT_EQ(1,writeMessage("", Lena, "LenaOut.bmp",1,1));
	ASSERT_EQ(1,writeMessage("1010", Lena, "LenaOut.bmp",1,1));
	ASSERT_EQ(1,writeMessage("1010", Lena, "LenaOut.bmp",1,0));
	ASSERT_EQ(1,writeMessage("1010", Lena, "LenaOut.bmp",2,1));
	ASSERT_EQ(1,writeMessage("1010", Lena, "LenaOut.bmp",2,0));
	ASSERT_EQ(1,writeMessage("1010", Lena, "LenaOut",1,1));
	ASSERT_EQ(0,writeMessage("1010", Lena, "LenaOut.bmp",0,1));
	ASSERT_EQ(0,writeMessage("1010", Lena, "LenaOut.bmp",0,0));
	ASSERT_EQ(0,writeMessage("", Lena, "",1,1));
	ASSERT_EQ(0,writeMessage("", LenaFail, "LenaOut.bmp",1,1));
	ASSERT_EQ(0,writeMessage("1010", LenaFail, "LenaOut.bmp",1,1));
 }
 
/*TEST(Steganography, extractMessageTest){
	BMP LenaB;
	LenaB.ReadFromFile("lenaB.bmp");
	string binary = "01010101";
	string binaryAll = addBinaryHeader( "text.txt");
	writeMessage(binaryAll, LenaB, "testFile.bmp", 1, true);
	
	string binary
	ASSERT_EQ(binary,extractMessage(LenaB,1,true).c_str());
}*/



int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
