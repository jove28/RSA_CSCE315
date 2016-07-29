#include "steganography.h"
using namespace std;

int main( int argc, char* argv[] ) {
    int choice = 1;
	int levels = 1;
	int grayscale = false;
	if( argc != 2 ) {
		cout << "Usage: <BMP_filename>"
			<< endl << endl;
		return 1;
	}

    string response;
    cout << "What do you want to do?\n1 - Embed\n2 - Extract\n3 - Both\n > ";
    cin >> response;
    int value = atoi(response.c_str());
    switch (value) {
        case 1:
            choice = 1;
            break;
        case 2:
            choice = 2;
            break;
        case 3:
            choice = 3;
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
    }

	cout << "How many levels? (1, 2)\n > ";
    cin >> response;

    value = atoi(response.c_str());
    switch (value) {
        case 1:
            levels = 1;
            break;
        case 2:
            levels = 2;
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
    }

    cout << "Is the image grayscale? (1 = Yes, 2 = No)\n > ";
    cin >> response;

    value = atoi(response.c_str());
    switch (value) {
        case 1:
            grayscale = true;
            break;
        case 2:
            grayscale = false;
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
    }

    string outputFilename = argv[1];
    //Embed Data
    if (choice == 1 || choice == 3) {
    	// declare and read the bitmap
    	BMP image;
    	image.ReadFromFile( argv[1]);

    	double maxSize = image.TellWidth() * image.TellHeight() * levels;
    	if ( !grayscale ) {
    		maxSize *= 3;
    	}
    	cout << "\nMax Size: " << maxSize << " bits\n\n";

        string binary;
        while (binary.size() == 0) {
            cout << "Which file would you like to encode?\n > ";
            cin >> response;
            binary = readFile(response);
        }
        binary = addBinaryHeader(binary, response);
        if ( binary.size() > maxSize ) {
        	cout << "Image cannot hold " << binary.size() << " of data! Terminating!\n\n";
        	return -1;
        }

        cout << "What should be the output filename? (***.bmp)\n > ";
        cin >> response;
        outputFilename = response;

        //cout << binary << "\n";
    	writeMessage(binary, image, outputFilename, levels, grayscale);
    }
    //Extract Data
    if (choice == 2 || choice == 3) {
    	BMP image2;
    	image2.ReadFromFile( outputFilename.c_str() );
    	string binary2 = extractMessage(image2, levels, grayscale);
    	extractHeaderAndWriteFile( binary2 );
    }
	
	return 0;
}