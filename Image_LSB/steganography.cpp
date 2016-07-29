//Created by Team: // No Comment
//For CSCE 315

#include "steganography.h"

using byte = unsigned char;
constexpr size_t BITS_PER_BYTE = 8;//numeric_limits<byte>::digits;
using bits_in_byte = bitset<BITS_PER_BYTE>;

//Gets the last or second to last bit
string getBit(int level, ebmpBYTE colorBit) {
	int binAnd = 0x01;
	for (int i = 0; i < level; ++i) {
		binAnd *= 2;
	}
	bitset<8> bits( binAnd & colorBit );
	bits >>= level;
	int bit = (int) bits.to_ulong();
	return to_string( bit );
}

//Sets the last or second to last bit
int setBit(int level, char binaryChar, ebmpBYTE colorBit) {
	int binAnd = 0xfe;
	int binOr = 0x01;
	//Calculate depending on level
	for (int i = 0; i < level; ++i) {
		binOr *= 2;
		binAnd = 0xff - binOr;
	}
	//Set bit
	if ( binaryChar == '0') {
		bitset<8> byte( binAnd & colorBit);
		return (int)(byte.to_ulong());
	}
	else {
		bitset<8> byte( binOr | colorBit );
		return (int)(byte.to_ulong());
	}
}

//Adds a header to a string of data
string addBinaryHeader(string bitstring, string path) {
	int dotPosition = path.find('.');
	string extension;
	//if there is an extension
	if ( dotPosition != -1 ) {
		extension = path.substr(dotPosition+1, string::npos);
	}
	int stringSize = bitstring.size();
	//Create Header
	string header = '\0' + extension + '\0' + to_string( stringSize ) + '\0';
	string bitHeader;
	for (int i = 0; i < header.size(); ++i) {
        bitHeader += bits_in_byte( byte( header[i] ) ).to_string();
    }
    //cout << "BitHeader: " << bitHeader << "\n";
    bitHeader += bitstring;
    return bitHeader;
}

//Extract the binary header
bool extractHeaderAndWriteFile( string bitstring ) {
	string extension;
	string sizeStr;
	int termCharsFound = 0;
	size_t i = 0;
	for( ; i < bitstring.size() && termCharsFound < 3 ; i += BITS_PER_BYTE ) {
        byte b = bits_in_byte( bitstring.substr( i, BITS_PER_BYTE ) ).to_ulong() ;
        //cout << "binary: " << bitstring.substr( i, BITS_PER_BYTE ) << "\n";
        if ( i == 0 && b != '\0' ) {
        	cout << "Header does not exist in this file! Terminating...\n";
        	return false;
        }
        if ( b == '\0' ) {
        	termCharsFound++;
        	//cout << termCharsFound << " Term Chars Found\n";
        }
        else if ( termCharsFound == 1 ) {
        	extension += b;
        	//cout << b << " Extension\n";
        }
        else if ( termCharsFound == 2 ) {
        	sizeStr += b;
        	//cout << b << " Size\n";
        }
    }
	int size = atoi( sizeStr.c_str() );
	if ( (size + i) > bitstring.size() ) {
		cout << "Unable to read " << size << " bits from the binary string of size " << bitstring.size() << "!\n";
		return false;
	}
	string message = bitstring.substr( i, size );
	//cout << "Should read " << size << " bits = actually read " << message.size() << " bits\n";
	bool wroteToFile = binaryToFile( message, extension );
	if ( !wroteToFile ) {
		cout << "Unable to write binary string to file\n";
		return false;
	}
	return true;
}

//Gets a file and adds the header data to it
string readFile( string path ) {
    string bitstring;
    ifstream file( path.c_str(), ios::binary );
    if ( file.fail() ) {
    	cout << "Unable to open " << path << "\n";
    	return "";
    }

    char c;
    while( file.get(c) ) {
        bitstring += bits_in_byte( byte(c) ).to_string();
    }
    //cout << "Initial Size of Bitstring: " << bitstring.size() << "\n";
    return bitstring;
}

//Writes a binary string to file
bool binaryToFile( string bitstring, string extension ) {
    while( bitstring.size()% BITS_PER_BYTE ) bitstring += '0';

    string path = "output";
    if ( extension.size() != 0 ) {
    	path += ".";
    	path += extension;
    }
    ofstream file( path.c_str(), ios::binary );

    for( size_t i = 0 ; i < bitstring.size() ; i += BITS_PER_BYTE ) {
        byte b = bits_in_byte( bitstring.substr( i, BITS_PER_BYTE ) ).to_ulong() ;
        file << b;
    }
    cout << "Created file named \"" << path << "\"\n";
    return true;
}

//Hide a message inside the 1-LSB plane of the BMP image
bool writeMessage(string strBinary, BMP image, string output_filename, int LSB_level, bool grayscale) {
	if (grayscale) {
		image.SetBitDepth(8);
		CreateGrayscaleColorTable( image );
	}
	else {
		image.SetBitDepth(24);
	}

	if ( LSB_level < 1 || LSB_level > 2) {
		cout << "LSB level \'" << to_string( LSB_level ) << "\' not supported.\n";
		return false;
	}
	else if ( output_filename == "" ) {
		cout << "File name is required!\n";
		return false; 
	}
	else if ( image.TellHeight() == 1 && image.TellWidth() == 1) {
		cout << "Image is invalid!\n";
		return false; 
	}

	int strCount = 0;
	for( int j=0 ; j < image.TellHeight() && strCount < strBinary.size(); j++) {
		for( int i=0 ; i < image.TellWidth() && strCount < strBinary.size(); i++) {
			//Red
			for (int k = LSB_level-1; k >= 0 && strCount < strBinary.size(); --k) {
				image(i,j)->Red = setBit(k, strBinary[strCount], image(i,j)->Red);
				//cout << "j: " << j << " i: " << i << " r: " << strBinary[strCount]; 
				strCount++;
			}
			if (grayscale) {
				strCount -= LSB_level;
			}
			if (strCount > strBinary.size()) { break; }
			//Green
			for (int k = LSB_level-1; k >= 0 && strCount < strBinary.size(); --k) {
				image(i,j)->Green = setBit(k, strBinary[strCount], image(i,j)->Green);
				//cout << "j: " << j << " i: " << i << " r: " << strBinary[strCount]; 
				strCount++;
			}
			if (grayscale) {
				strCount -= LSB_level;
			}
			if (strCount > strBinary.size()) { break; }
			//Blue
			for (int k = LSB_level-1; k >= 0 && strCount < strBinary.size(); --k) {
				image(i,j)->Blue = setBit(k, strBinary[strCount], image(i,j)->Blue);
				//cout << " b: " << strBinary[strCount] << "\n"; 
				strCount++;
			}
			//cout << "R: " << to_string(image(i,j)->Red) << " G: " << to_string(image(i,j)->Green) << " B: " << to_string(image(i,j)->Blue) << "\n";
		}
	}
	image.WriteToFile( output_filename.c_str() );
	return true;
}

//Extract a message from the LSB plane of the BMP image
string extractMessage(BMP image, int LSB_level, bool grayscale) {
	string strBinary;
	for( int j=0 ; j < image.TellHeight(); j++) {
		for( int i=0 ; i < image.TellWidth(); i++) {
			for (int k = LSB_level-1; k >= 0; --k) {
				strBinary += getBit(k, image(i,j)->Red);
				//cout << "j: " << j << " i: " << i << " r: " << to_string(image(i,j)->Red) ; 
			}
			//Change 'GB' if in RGB
			if (!grayscale)	{
				for (int k = LSB_level-1; k >= 0; --k) {
					strBinary += getBit(k, image(i,j)->Green);
					//cout << " g: " << to_string(image(i,j)->Green); 
				}

				for (int k = LSB_level-1; k >= 0; --k) {
					strBinary += getBit(k, image(i,j)->Blue);
					//cout << " b: " << to_string(image(i,j)->Blue) << "\n"; 
				}
			}		
		}
	}
	return strBinary;
}

//Returns whether the two images are the same (ie have the same bit sequence)
bool sameImage(string image1Name, string image2Name, bool grayscale) {
    BMP image1;
    BMP image2;
    image1.ReadFromFile( image1Name.c_str() );
    image2.ReadFromFile( image2Name.c_str() );

    string bitstring1LSB1 = extractMessage(image1, 8, grayscale);
    string bitstring2LSB1 = extractMessage(image2, 8, grayscale);
    if (bitstring1LSB1 == bitstring2LSB1) {
        return true;
    }
    return false;
}

//Writes random numbers to the LSB to void any previous message
bool nullImage(BMP image, int LSB_level, bool grayscale, string image1Name) {
	if (grayscale) {
		image.SetBitDepth(8);
	}
	else {
		image.SetBitDepth(24);
	}
	if ( LSB_level < 1 || LSB_level > 2) {
		cout << "LSB level \'" << to_string( LSB_level ) << "\' not supported.\n";
		return false;
	}
	else if ( image.TellHeight() == 1 && image.TellWidth() == 1) {
		cout << "Image is invalid!\n";
		return false; 
	}
	srand ( time(NULL) );
	int rnd;
	for( int j=0 ; j < image.TellHeight(); j++) {
		for( int i=0 ; i < image.TellWidth(); i++) {
			for (int k = LSB_level-1; k >= 0; --k) {
				rnd = rand() % 2;
				char c = to_string( rnd ).c_str()[0];
				image(i,j)->Red = setBit(k, c, image(i,j)->Red);
				if ( getBit(k, image(i,j)->Red)[0] != c ) {
					cout << "Did not write bit! " << getBit(k, image(i,j)->Red)[0] << " != " << c << "\n";
				}
			}
			for (int k = LSB_level-1; k >= 0; --k) {
				rnd = rand() % 2;
				char c = to_string( rnd ).c_str()[0];
				image(i,j)->Green = setBit(k, c, image(i,j)->Green);
			}

			for (int k = LSB_level-1; k >= 0; --k) {
				rnd = rand() % 2;
				char c = to_string( rnd ).c_str()[0];
				image(i,j)->Green = setBit(k, c, image(i,j)->Green);
			}
		}
	}
	if(grayscale) {
		CreateGrayscaleColorTable( image );
	}
    image.WriteToFile( image1Name.c_str() );
	return true;
}