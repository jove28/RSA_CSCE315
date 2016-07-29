#include "steganography.h"

int main( int argc, char* argv[] ) {
	if( argc != 2 ) {
        cout << "Usage: <BMP_filename>"
            << endl << endl;
        return 1;
    }
    string response;
    bool grayscale = false;
    int test = 1;
    cout << "\nWhich test do you want to run?\n1 - Compare with original\n2 - Null Image Data\n > ";
    cin >> response;
    int value = atoi(response.c_str());
    switch (value) {
        case 1:
            test = 1;
            break;
        case 2:
            test = 2;
            break;
        default:
            cout << "Invalid choice" << endl;
            return -1;
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
            return -1;
    }
    string image1Name = argv[1];
    if (test == 1) {
        cout << "What is the filename for the original image?\n > ";
        cin >> response;
        string image2Name = response;
        if ( sameImage(image1Name, image2Name, grayscale) ) {
            cout << "The image has NOT been modified.\n";
        }
        else {
            cout << "The image HAS been modified! There might be hidden data!\n";
        }
    }
    else if (test == 2) {
        cout << "How many levels do you want to null? (1, 2)\n > ";
        cin >> response;
        int levels = atoi(response.c_str());
        if (levels < 1 || levels > 2) {
            cout << "Level \'" << levels << "\' is not supported.\n";
            return -1;
        }
        BMP image;
        image.ReadFromFile( image1Name.c_str() );
        if ( !nullImage(image, levels, grayscale, image1Name) ) {
            cout << "Unable to null image\n";
            return -1;
        }
        cout << "Image data has been nulled!\n";
    }
	return 0;
}