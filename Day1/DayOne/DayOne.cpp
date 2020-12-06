// DayOne.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> SearchEntries(vector<int> intEntry, int value) // Returns a vector [First value's position; Second value's position; Second value's position; Product]
{
	vector<int> vector;
	int sum = 0;
	int i, j, k;

	for (i = 0; i < intEntry.size(); i++)
	{
		for (j = 0; j < intEntry.size(); j++)
		{
			for (k = 0; k < intEntry.size(); k++)
			{
				sum = intEntry[i] + intEntry[j] + intEntry[k];

				if (sum == value)
				{
					break;
				}
			}

			if (sum == value)
			{
				break;
			}
		}

		if (sum == value)
		{
			break;
		}
		
	}

	vector.push_back(i);
	vector.push_back(j);
	vector.push_back(k);

	return vector;
}

int multiply(vector<int> intEntry, vector<int> indices)
{
	int product = 1;

	for (int i = 0; i < indices.size(); i++)
	{
		product = intEntry[indices[i]] * product;
	}

	return product;
}

int main()
{
	ifstream input;
	string stringEntry;
	vector<int> intEntry;
	int value = 2020;

	input.open("input.txt", ios_base::in);

	if (!input.is_open())
	{
		cout << "Unable to open file";
	}
	else
	{
		while (getline(input, stringEntry))
		{
			intEntry.push_back(stoi(stringEntry));
		}
		input.close();
	
		auto indices = SearchEntries(intEntry, value);

		for (int i = 0; i < indices.size(); i++)
		{
			if(indices[i] > intEntry.size())
			{
				cout << "No value found" << endl;
				break;
			}
			else
			{
				cout << "Value " << i + 1 << ": " << intEntry[indices[i]] << endl;
			}

		}
		
		cout << "The product is: " << multiply(intEntry, indices);
		
	}
	
	return 0;
}
