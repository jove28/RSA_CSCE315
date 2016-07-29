#include <iostream>
#include <fstream>
#include "SudokuSolver.h"

//Solve Sudoku puzzles
//Input is a string of 81 characters
//Input each block without space or enter.
//Input 0 for empty.
//If you put less than 81 it fills it in itself.
using namespace std;
pair<bool, array<int, 81>> solve(const char* in)
{
    array<int, 81> answers;
    int* map = answers.data(); 
    int empty[81]; 
    int cur_index = 0; 
    int cur_row; 
	int cur_column; 
	int region_index; 
    int temp_bit;
    int empty_count = 0; 
    int filled = 0; 
    int col[9]; 
	int row[9]; 
	int region[9]; 
    for (int i = 0; i < 9; i++)
    {
        col[i] = row[i] = region[i] = 01776; 
    }
    while (*in)
    {
        if (*in == '0') // Empty grid
        {
            empty[empty_count++] = cur_index;
            map[cur_index] = 0;

        }
        else if ((*in) <= '9' && (*in) >= '1') // Non empty grid
        {
            cur_row = cur_index / 9;
            cur_column = cur_index % 9;
            region_index = (cur_index / 27) * 3 + ((cur_index % 9) / 3);
            map[cur_index] = (*in) - '0';
            temp_bit = (1 << map[cur_index]); // Check if the grid is wrong
            if ((temp_bit & row[cur_row] & col[cur_column] & region[region_index]) == 0) {
                return pair<bool, array<int, 81>>(false, answers);
            }
            // Fill the bit to 0 for the row, column and region
            row[cur_row] ^= temp_bit;
            col[cur_column] ^= temp_bit;
            region[region_index] ^= temp_bit;
        }
        else
        {
            break;
        }
        in++;
        cur_index++;
    }
    for (; cur_index < 81; cur_index++) //Fill empty for left grids
    {
        empty[empty_count++] = cur_index;
        map[cur_index] = 0;
    }
    while (filled < empty_count) //Fill numbers until all number has been filled
    {
        cur_index = empty[filled];
        cur_row = cur_index / 9;
        cur_column = cur_index % 9;
        region_index = (cur_index / 27) * 3 + ((cur_index % 9) / 3);
        if (map[cur_index] > 0)  //If this grid has been filled before, then reset it
        {
            temp_bit = (1 << map[cur_index]); //Reset the bit to 1
            row[cur_row] |= temp_bit;
            col[cur_column] |= temp_bit;
            region[region_index] |= temp_bit;
        }
        while (map[cur_index] <= 9) //Fill current grid if the number was not appeared in current row, col or region
        {
            map[cur_index] ++;
            temp_bit = (1 << map[cur_index]); //Get the bit of the number and check if it has already existed.
            if (row[cur_row] & col[cur_column] & region[region_index] & temp_bit)
            {
                break;
            }
        }
        if (map[cur_index] > 9) // If there is no number to fill, back to the grid we filled before
        {
            map[cur_index] = 0;
            filled--;
            if (filled < 0) // If current is the first grid, then there is no answer for the puzzle
            {
                return pair<bool, array<int, 81>>(false, answers);
            }
        }
        else
        {
            //After we filled this grid, set the bit to 0
            row[cur_row] ^= temp_bit;
            col[cur_column] ^= temp_bit;
            region[region_index] ^= temp_bit;
            filled++;
        }
    }
    return pair<bool, array<int, 81>>(true, answers);
}
bool puzzle_solved(const char* in){
	array<int, 81> answers;
    int* map = answers.data(); 
    int empty[81]; 
    int cur_index = 0; 
    int cur_row; 
	int cur_column; 
	int region_index; 
    int temp_bit;
    int empty_count = 0; 
    int filled = 0; 
    int col[9]; 
	int row[9]; 
	int region[9]; 
    for (int i = 0; i < 9; i++)
    {
        col[i] = row[i] = region[i] = 01776; 
    }
    while (*in)
    {
        if (*in == '0') // Empty grid
        {
            empty[empty_count++] = cur_index;
            map[cur_index] = 0;

        }
        else if ((*in) <= '9' && (*in) >= '1') // Non empty grid
        {
            cur_row = cur_index / 9;
            cur_column = cur_index % 9;
            region_index = (cur_index / 27) * 3 + ((cur_index % 9) / 3);
            map[cur_index] = (*in) - '0';
            temp_bit = (1 << map[cur_index]); // Check if the grid is wrong
            if ((temp_bit & row[cur_row] & col[cur_column] & region[region_index]) == 0) {
                pair<bool, array<int, 81>> ans(false, answers);
				return ans.first;
            }
            // Fill the bit to 0 for the row, column and region
            row[cur_row] ^= temp_bit;
            col[cur_column] ^= temp_bit;
            region[region_index] ^= temp_bit;
        }
        else
        {
            break;
        }
        in++;
        cur_index++;
    }
    for (; cur_index < 81; cur_index++) //Fill empty for left grids
    {
        empty[empty_count++] = cur_index;
        map[cur_index] = 0;
    }
    while (filled < empty_count) //Fill numbers until all number has been filled
    {
        cur_index = empty[filled];
        cur_row = cur_index / 9;
        cur_column = cur_index % 9;
        region_index = (cur_index / 27) * 3 + ((cur_index % 9) / 3);
        if (map[cur_index] > 0)  //If this grid has been filled before, then reset it
        {
            temp_bit = (1 << map[cur_index]); //Reset the bit to 1
            row[cur_row] |= temp_bit;
            col[cur_column] |= temp_bit;
            region[region_index] |= temp_bit;
        }
        while (map[cur_index] <= 9) //Fill current grid if the number was not appeared in current row, col or region
        {
            map[cur_index] ++;
            temp_bit = (1 << map[cur_index]); //Get the bit of the number and check if it has already existed.
            if (row[cur_row] & col[cur_column] & region[region_index] & temp_bit)
            {
                break;
            }
        }
        if (map[cur_index] > 9) // If there is no number to fill, back to the grid we filled before
        {
            map[cur_index] = 0;
            filled--;
            if (filled < 0) // If current is the first grid, then there is no answer for the puzzle
            {
                pair<bool, array<int, 81>> ans(false, answers);
				return ans.first;
            }
        }
        else
        {
            //After we filled this grid, set the bit to 0
            row[cur_row] ^= temp_bit;
            col[cur_column] ^= temp_bit;
            region[region_index] ^= temp_bit;
            filled++;
        }
    }
    pair<bool, array<int, 81>> ans(true, answers);
	return ans.first;
}

void sudokuToFile(string filename, pair<bool, array<int, 81>> p){
	ofstream out;
	out.open(filename);
	for(int i=1; i<=81; ++i){
		out<<p.second[i-1]<<" ";
		if(i % 9 == 0)
			out<<endl;
	}
	out.close();
}
/*int main()
{
    string input;
    cin >> input;
    pair<bool, array<int, 81>> pair = solve(input.c_str());
	bool solved=puzzle_solved(input.c_str());
	cout<<"Solved: "<<solved<<endl;
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
