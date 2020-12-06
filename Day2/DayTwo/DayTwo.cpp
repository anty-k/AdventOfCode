// DayTwo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class PasswordEntry
{
protected: 
	int min, max;
	char character;
	string password;
public:
	void ExtractValues(string fileLine);
	virtual bool PasswordValidity() = 0;
};

void PasswordEntry::ExtractValues(string fileLine)
{
	int sepPosition;

	for (int i = 0; i < fileLine.length(); i++)
	{
		if (fileLine[i] == '-')
		{
			min = stoi(fileLine.substr(0,i));
			sepPosition = i;
		}

		if (fileLine[i] == ' ' && fileLine[i-1] != ':')
		{
			max = stoi(fileLine.substr(sepPosition + 1, i - sepPosition - 1));
			sepPosition = i;
		}

		if (fileLine[i] == ':')
		{
			character = fileLine[sepPosition + 1];
			sepPosition = i;
		}

		if (i == fileLine.length()-1)
		{
			password = fileLine.substr(sepPosition + 2, fileLine.length() - sepPosition - 1);
		}
	}
}

class line : public PasswordEntry
{
	public:
	virtual bool PasswordValidity() override;
};

bool line::PasswordValidity()
{
	int count = 0;

	for (int i = 0; i < password.length(); i++)
	{
		if (password[i] == character) count++;
	}

	if (count >= min && count <= max)
	{
		return true;
	}
	else
	{
		return false;
	}
}

class correctedLine : public PasswordEntry
{
public:
	virtual bool PasswordValidity() override;
};

bool correctedLine::PasswordValidity()
{
	int count = 0;
	vector<int> inputs{ min - 1, max - 1 };
	for (int i : inputs)
	{
		if (password[i] == character)
		{
			count++;
		}
	}

	if (count == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	ifstream input;

	input.open("input.txt", ios_base::in);


	if (!input.is_open())
	{
		cout << "Unable to open file" << endl;
	}
	else
	{
		string strLine;
		correctedLine fileLine;
		int count = 0;

		while (getline(input, strLine))
		{
			fileLine.ExtractValues(strLine);
			
			if (fileLine.PasswordValidity())
			{
				count++;
			}
		}
		input.close();

		cout << count << " passwords are valid." << endl;
	}

	return 0;
}

