// Game of life rules and data
#ifndef GOFL_H_
#define GOFL_H_

#include <iostream>
#include <fstream>

using namespace std;

#define MAX_SIZE 25

class GOFL
{
    // This is the whole table for the game
    // the new game of life table is for iteration purposes
    int gofl_table[MAX_SIZE][MAX_SIZE];
    int new_gofl_table[MAX_SIZE][MAX_SIZE];

    public:
    // set_values picks a file and put it in gofl_table
    void set_values(fstream&);
    // write_output puts new_gofl_table in a text file
    void write_output(fstream&);
    // write_output_bin puts new_gofl_table in a binary file
    void write_output_bin(fstream&);
    // does one iteration on gofl_table
    void next_step();
};

void GOFL::set_values(fstream& input_file)
{
    for(int c_row = 0; c_row < MAX_SIZE; c_row++)
    {
        for(int c_column = 0; c_column < MAX_SIZE; c_column++)
        {
            char buffer;
            input_file.read(&buffer, 1);
            if (buffer == '1') gofl_table[c_row][c_column] = 1;
            else if (buffer == '0') gofl_table[c_row][c_column] = 0;
            else cout << "ERROR: invalid character read!" << endl;
        }
    }
}

void GOFL::write_output(fstream& output_file)
{
    for(int c_row = 0; c_row < MAX_SIZE; c_row++)
    {
        for(int c_column = 0; c_column < MAX_SIZE; c_column++)
        {
            output_file << gofl_table[c_row][c_column] << " ";
        }
        output_file << "\n";
    }
}


void GOFL::write_output_bin(fstream& output_file)
{
    for(int c_row = 0; c_row < MAX_SIZE; c_row++)
    {
        for(int c_column = 0; c_column < MAX_SIZE; c_column++)
        {
            output_file.write((char*)&(gofl_table[c_row][c_column]), sizeof(gofl_table[c_row][c_column]));
        }
    }
}

void GOFL::next_step()
{
    int neighbor_counter;

    for(int c_row = 0; c_row < MAX_SIZE; c_row++)
    {
        for(int c_column = 0; c_column < MAX_SIZE; c_column++)
        {
            // counting neighbors
            neighbor_counter = 0;
            for(int i = -1; i <= 1; i++)
            {
                for(int j = -1; j <= 1; j++)
                {
                    if(!(i == 0 && j == 0) && c_row+i >= 0 && c_column+j >= 0 && c_row+i <= (MAX_SIZE-1) && c_column+j <= (MAX_SIZE-1))
                    {
                        neighbor_counter += gofl_table[c_row+i][c_column+j];
                    } 
                }
            }

            // game of life rules:
            // if the cell is dead but has 3 neighbors, lives on next generation
            if(gofl_table[c_row][c_column] == 0 && neighbor_counter == 3)
            {
                new_gofl_table[c_row][c_column] = 1;
            }
            // if the cell is alive and have less then 2 or more than 3 neighbors, it dies
            else if(gofl_table[c_row][c_column] == 1 && (neighbor_counter < 2 || neighbor_counter > 3))
            {
                new_gofl_table[c_row][c_column] = 0; 
            } 
            // if the cell is alive and has 2 or 3 neighbors, lives on next generation
            else
            {
                new_gofl_table[c_row][c_column] = gofl_table[c_row][c_column];
            }
        }
    }

    // copying new_gofl_table to gofl_table
    for(int c_row = 0; c_row < MAX_SIZE; c_row++)
    {
        for(int c_column = 0; c_column < MAX_SIZE; c_column++)
        {
            gofl_table[c_row][c_column] = new_gofl_table[c_row][c_column];
        }
    }


}

#endif // GOFL_H_
