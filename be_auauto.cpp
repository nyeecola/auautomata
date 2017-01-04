#include <iostream>
#include <fstream>
#include "gofl.h"

using namespace std;

int main ()
{	
	fstream input_file;
	fstream output_file;

	input_file.open("automata.in", ios::in | ios::binary);
	output_file.open("automata.out", ios::out | ios::binary);

	if (!(input_file.is_open() && output_file.is_open()))
	{
		cout << "Error on file read" << endl;
	}
	
	GOFL gofl;

	gofl.set_values(input_file);
	
	gofl.next_step();


	gofl.write_output(output_file);

	output_file.close();
	input_file.close();

	return 0;
}

