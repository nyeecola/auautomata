
#ifndef GOFL_H_
#define GOFL_H_

#include <iostream>
#include <fstream>

using namespace std;

#define MAX_SIZE 25

class GOFL
{
  bool gofl_table[MAX_SIZE][MAX_SIZE];
  bool new_gofl_table[MAX_SIZE][MAX_SIZE];

  public:
  void set_values(fstream&);
  void write_output(fstream&);
  void write_output_bin(fstream&);
  void next_step();
};

void GOFL::set_values(fstream& input_file)
{
  for(int c_row = 0; c_row < MAX_SIZE; c_row++)
  {
    for(int c_column = 0; c_column < MAX_SIZE; c_column++)
    {
      input_file.read((char*) &(gofl_table[c_row][c_column]), sizeof(gofl_table[0][0]));
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

      if(gofl_table[c_row][c_column] == 0 && neighbor_counter == 3)
      {
        new_gofl_table[c_row][c_column] = 1;
      } else if(gofl_table[c_row][c_column] == 1 && (neighbor_counter < 2 || neighbor_counter > 3))
      {
        new_gofl_table[c_row][c_column] = 0; 
      } else
      {
        new_gofl_table[c_row][c_column] = gofl_table[c_row][c_column];
      }
    }
  }

  for(int c_row = 0; c_row < MAX_SIZE; c_row++)
  {
    for(int c_column = 0; c_column < MAX_SIZE; c_column++)
    {
      gofl_table[c_row][c_column] = new_gofl_table[c_row][c_column];
    }
  }


}

#endif // GOFL_H_
