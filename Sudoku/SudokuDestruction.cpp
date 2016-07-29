#include "SudokuDestruction.h"
//Destroy Sudoku puzzle
//Input is a string of 81 characters
//Input each block without space or enter.
//Input 0 for empty.
//If you put less than 81 it fills it in itself.
using namespace std;
pair<bool, array<int, 81>> destroy(const char* in)
{
    array<int, 81> answers;
	srand(time(NULL));
    for(int i=0;i<answers.size();i++){
		int dest= rand() % 9 + 1;
		answers[i]=dest;
	}
    return pair<bool, array<int, 81>>(true, answers);
}

bool puzzle_destroyed(const char* in){
	array<int, 81> answers;
	srand(time(NULL));
    for(int i=0;i<answers.size();i++){
		int dest= rand() % 9 + 1;
		answers[i]=dest;
	}
    pair<bool, array<int, 81>> ans(true, answers);
	return ans.first;
}

/*int main()
{
    string input;
    cin >> input;
    pair<bool, array<int, 81>> pair = destroy(input.c_str());
    if (pair.first)
    {
        array<int, 81> ans = pair.second;
        for (int i = 0; i < 81; i++)
        {
            cout << ans[i];
            if (i % 9 == 8)
            {
                cout << endl;
            }
            else
            {
                cout << " ";
            }
        }
    }
    else
    {
        cout << "No answer" << endl;
    }
}*/
