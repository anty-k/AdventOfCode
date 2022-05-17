// DayOne.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void takeStairs(char instruction, int &stair)
{
	if (instruction == '(')
	{
		stair++;
		return;
	}
	stair--;
}

int main()
{
	string filename("input.txt");
	char byte;
	int stair = 0;
	int basementInstruction;
	bool basementReached = false;

	ifstream input_file(filename);

	if (!input_file.is_open())
	{
		cout << "Unable to open file";
		return 0;
	}
	
	int i = 0;
	while (input_file.get(byte))
	{
		takeStairs(byte, stair);
		i++;

		if (stair == -1 && !basementReached)
		{
			basementReached = true;
			basementInstruction = i;
		}
	}

	input_file.close();

	cout << "Santa, go to the " << stair << " floor!" << endl;
	cout << "First basement floor reached at the " << basementInstruction << "th instruction" << endl;

	return 0;
}
