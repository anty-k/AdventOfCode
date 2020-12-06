
#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>

using namespace std;

int Position(string line, int deltaX, int currentPosition)
{
	int newPosition = (currentPosition + deltaX) % line.size();

	return newPosition;
}

bool IsTree(string line, int currentPosition)
{
	return line[currentPosition] == '#';
}

int main()
{
	ifstream input;

	input.open("input.txt", ios_base::in);


	if (!input.is_open())
	{
		cout << "Unable to open file" << endl;
		return 0;
	}

	int64_t product = 1;
	int	count;
	vector<int> deltaX({1,3,5,7,1});
	vector<int> deltaY({1,1,1,1,2});

	for (int i = 0; i < deltaX.size(); i++)
	{
		string line;
		count = 0;
		int currentPosition = 0, lineNumber = 0;

		while (getline(input, line))
		{
			if (lineNumber % deltaY[i] != 0)
			{
				lineNumber++;
				continue;
			}

			if (IsTree(line, currentPosition))
			{
				count++;
			}

			lineNumber++;
			currentPosition = Position(line, deltaX[i], currentPosition);
		}

		input.clear();
		input.seekg(0);

		product = product * count;
		cout << count << ", " << product << endl;
	}
	input.close();

	// cout << count << " trees encountered." <<  endl;
	cout << "The product of trees encountered is: " << product << endl;
}
