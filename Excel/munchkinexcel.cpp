#include "CSVsteganography.h"
using namespace std;

int main( int argc, char* argv[] ) {
    int choice = 1;
    if( argc != 2 ) {
        cout << "Usage: <CSV_filename>"
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

    string filename = argv[1];
    //Embed a message into a CSV
    if (choice == 1 || choice == 3) {
        //find the number of commas
        ifstream infile( filename.c_str() );
        if (infile.fail()) {
            cout << "File \'" << filename << "\' does not exist. Terminating!\n";
            return -1;
        }
        string line;
        getline( infile, line );
        int numCommas = numberOfCommas(line);
        infile.close();

        cout << "What is your message?\n > ";
        string message;
        cin.ignore();
        getline(cin, message);

        int blankLines = -1;
        while ( blankLines < 0 || blankLines > 500) {
            cout << "How many blank lines do you want between the real content and the hidden message?\n > ";
            cin >> response;
            blankLines = atoi(response.c_str());
            if ( blankLines < 0 || blankLines > 500 ) {
                cout << "Please provide a number between 0-500\n";
            }
        }

        vector<string> cellsVec = createCells(message);
        string cellsStr = cellsToString(cellsVec, numCommas, blankLines);

        ofstream outfile;
        outfile.open(filename, ios_base::app); //Append the data
        outfile << cellsStr;    

        cout << "Hidden message added to \'" << filename << "\'\n";
    }
    //Extract from the CSV
    if (choice == 2 || choice == 3) {
        ifstream infile( filename.c_str() );
        if (infile.fail()) {
            cout << "File \'" << filename << "\' does not exist. Terminating!\n";
            return -1;
        }

        string totalString;
        string str;
        while (getline(infile, str)) {
            totalString += str;
            totalString += "\n";
        }

        vector<string> cells = extractCells(totalString);
        vector<int> spacesVec = detectSpaces(cells);
        string message = numbersToString(spacesVec);

        cout << "Encoded Message: \n" << message << "\n";
    }
    return 0;
}