#include "EasyBMP.h"
#include <bitset>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

string getBit(int level, ebmpBYTE colorBit);
int setBit(int level, char binaryChar, ebmpBYTE colorBit);
string addBinaryHeader(string bitstring, string path);
bool extractHeaderAndWriteFile( string bitstring );
string readFile( string path );
bool binaryToFile( string bitstring, string extension );
bool writeMessage(string strBinary, BMP image, string output_filename, int LSB_level = 1, bool grayscale = false);
string extractMessage(BMP image, int LSB_level = 1, bool grayscale = false);
bool sameImage(string image1Name, string image2Name, bool grayscale);
bool nullImage(BMP image, int LSB_level = 1, bool grayscale = false, string image1Name = "output.bmp");