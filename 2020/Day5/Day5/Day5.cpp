#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Seat {
private:
	int row = 0;
	int column = 0;

private:
	int ConvertToRow(string rowCode);
	int ConvertToColumn(string columnCode);
public:
	void CodeSplit(string code);
	int ID();
};

int Seat::ConvertToRow(string rowCode)
{
	for (int i = 0; i < rowCode.size() ; i++)
	{
		if (rowCode[i] == 'B')
		{
			row += 1 << (rowCode.size() - i - 1);
		}
	}

	return row;
}

int Seat::ConvertToColumn(string columnCode)
{
	for (int i = 0; i < columnCode.size(); i++)
	{
		if (columnCode[i] == 'R')
		{
			column += 1 << (columnCode.size() - i - 1);
		}
	}

	return column;
}

void Seat::CodeSplit(string code)
{
	row = ConvertToRow(code.substr(0, 7));
	column = ConvertToColumn(code.substr(7, 3));
}

int Seat::ID()
{
	return row * 8 + column;
}

int FindMySeat(vector<int> IDs)
{
	sort(IDs.begin(), IDs.end());
	
	int firstSeat = *IDs.begin(), i = 0;

	while (firstSeat + i == IDs[i])
	{
		i++;
	}

	return firstSeat + i;
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

	string entry;
	vector<int> IDs;

	while (getline(input, entry))
	{
		Seat seat;

		seat.CodeSplit(entry);
		IDs.push_back(seat.ID());
	}

	auto maxID = max_element(IDs.begin(), IDs.end());
	cout << "Max ID is " << *maxID << endl;

	int mySeat = FindMySeat(IDs);

	cout << "My seat has the ID " << mySeat << endl;

	return 0;
}