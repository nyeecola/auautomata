#include <iostream>
#include <fstream>

#define MAX_SIZE 25

using namespace std;

int main ()
{
	fstream input_file;
	fstream output_file;

	input_file.open("doggy.txt", ios::in);
	output_file.open("automata.in", ios::out | ios::binary);

	char cur_numb_read;
	for(int c_row = 0; c_row < MAX_SIZE; c_row++)
	{
		for(int c_column = 0; c_column < MAX_SIZE; c_column++)
		{
			input_file >> cur_numb_read;
			output_file.write(&cur_numb_read, 1);
		}
	}


}

