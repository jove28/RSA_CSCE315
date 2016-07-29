#include "CSVsteganography.h"

int main( int argc, char* argv[] ) {
    if( argc != 2 ) {
        cout << "Usage: <CSV_filename>"
            << endl << endl;
        return 1;
    }
    string response;
    int test = 1;
    cout << "\nWhich test do you want to run?\n1 - Check For Hidden Data\n2 - Null Hidden Data\n > ";
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
    string filename = argv[1];
    //Embed Data
    if (test == 1) {
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
        cout << "# of spaces in \"empty\" cells:\n";
        for (int i = 0; i < spacesVec.size(); ++i) {
            cout << spacesVec[i] << " ";
        }
        cout << "\n";
    }
    //Extract Data
    else if (test == 2) {
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

        int numCommas = numberOfCommas(totalString);
        vector<string> cells = extractCells(totalString);
        vector<string> noSpacesVec = deleteSpaces(cells);
        string fileStr = cellsToString(noSpacesVec, numCommas, 0, true);

        ofstream outfile;
        outfile.open(filename, ios_base::trunc); //Remove existing data
        outfile << fileStr;    

        cout << "Nulled hidden data in \'" << filename << "\'\n";
    }
    return 0;
}