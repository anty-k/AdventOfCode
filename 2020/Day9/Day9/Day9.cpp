// Day9.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

int Max(vector<int> vector)
{
	int max = 0;

	for (int i = 0; i < vector.size(); i++)
	{
		if (vector[i] > max)
		{
			max = vector[i];
		}
	}

	return max;
}

bool IsSum(const vector<int>& numberSerie)
{
	for (int i = 0; i < numberSerie.size() - 1; i++)
	{
		int diff = numberSerie[numberSerie.size() - 1] - numberSerie[i];
		
		for (int j = 0; j < numberSerie.size() - 1; j++)
		{
			if(i == j) continue;

			if (diff == numberSerie[j]) return true;
		}
	}

	return false;
}

int FindWeakness(const vector<int>& completeSerie)
{
	for(int i = 0; i < completeSerie.size() - 2; i++)
	{
		int sum = 0;
		int j;

		for (j = i; j < completeSerie.size() - 2; j++)
		{
			sum += completeSerie[j];

			if (sum == completeSerie[completeSerie.size() - 1])
			{
				vector<int> subVector(&completeSerie[i + 1], &completeSerie[j + 1]);
				int max = Max(subVector);

				for (int k = 0; k < subVector.size(); k++)
				{
					cout << subVector[k] << endl;
				}

				return completeSerie[i + 1] + max;
			}

			if (sum > completeSerie[completeSerie.size() - 1]) break;
		}
	}

	return 0;
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

	string inputLine;
	vector<int> numberSerie, completeSerie;
	int preambleSize = 25, i = 0;

	while (getline(input, inputLine))
	{
		int number = stoi(inputLine);

		if (i < preambleSize + 1)
		{
			numberSerie.push_back(number);
		}
		else 
		{
			if (!IsSum(numberSerie)) 
			{
				cout << "The first number not to be a sum is " << numberSerie[numberSerie.size() - 1] << endl;

				cout << "The encryption weakness is: " << FindWeakness(completeSerie) << endl;
				break;
			}

			numberSerie.push_back(number);
			numberSerie.erase(numberSerie.begin());
		}

		completeSerie.push_back(number);

		i++;
	}
}

