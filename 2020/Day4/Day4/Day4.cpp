// Day4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Passport
{
public :
	string byr; // Birth year
	string iyr; // Issue year
	string eyr; // Expiration year
	string hgt; // Height
	string hcl; // Hair color
	string ecl; // Eye color
	string pid; // Passport ID
	string cid; // Country ID

private:
	string ReadPassportEntry(string inputPassport, string Entry);
	bool BirthYearIsValid();
	bool IssueYearIsValid();
	bool ExpirationYearIsValid();
	bool HeightIsValid();
	bool HairColorIsValid();
	bool EyeColorIsValid();
	bool PassportIDIsValid();
	bool CountryIDIsValid();

public:
	void CreatePassport(string InputPassport);
	bool IsValid();
};

string Passport::ReadPassportEntry(string inputPassport, string Entry)
{
	int begining, ending;
	auto pos = inputPassport.find(Entry);

	if (pos == string::npos)
	{
		return "";
	}

	begining = pos + Entry.size() + 1;
	ending = inputPassport.find(" ", begining);
	return inputPassport.substr(begining, ending - begining);
}	

void Passport::CreatePassport(string InputPassport)
{
	this->byr = this->ReadPassportEntry(InputPassport, "byr");
	this->eyr = this->ReadPassportEntry(InputPassport, "eyr");
	this->iyr = this->ReadPassportEntry(InputPassport, "iyr");
	this->hgt = this->ReadPassportEntry(InputPassport, "hgt");
	this->hcl = this->ReadPassportEntry(InputPassport, "hcl");
	this->ecl = this->ReadPassportEntry(InputPassport, "ecl");
	this->pid = this->ReadPassportEntry(InputPassport, "pid");
	this->cid = this->ReadPassportEntry(InputPassport, "cid");

	return;
}

bool Passport::IsValid()
{
	if (byr.empty() || eyr.empty() || iyr.empty() || hgt.empty() || hcl.empty() || ecl.empty() || pid.empty())
	{
		return false;
	}

	if (!this->BirthYearIsValid() ||
		!this->IssueYearIsValid() ||
		!this->ExpirationYearIsValid() ||
		!this->HeightIsValid() ||
		!this->HairColorIsValid() ||
		!this->EyeColorIsValid() ||
		!this->PassportIDIsValid())
	{
		return false;
	}

	return true;
}

bool Passport::BirthYearIsValid()
{
	if (byr.size() != 4)
	{
		return false;
	}
	try 
	{
		int birthYear = stoi(byr);
		return (birthYear >= 1920 && birthYear <= 2002);
	}
	catch(...)
	{
		return false;
	}
}

bool Passport::IssueYearIsValid()
{
	if (iyr.size() != 4)
	{
		return false;
	}

	try
	{
		int issueYear = stoi(iyr);
		return (issueYear >= 2010 && issueYear <= 2020);
	}
	catch (...)
	{
		return false;
	}
}

bool Passport::ExpirationYearIsValid()
{
	if (eyr.size() != 4)
	{
		return false;
	}

	try
	{
		int expirationYear = stoi(eyr);
		return (expirationYear >= 2020 && expirationYear <= 2030);
	}
	catch (...)
	{
		return false;
	}
}

bool Passport::HeightIsValid()
{
	if (hgt.size() < 2)
	{
		return false;
	}
	
	string unit = hgt.substr(hgt.size()-2, 2);
	int min, max;
	
	if (unit == "cm")
	{
		max = 193;
		min = 150;
	}
	else if (unit == "in")
	{
		max = 76;
		min = 59;
	}
	else
	{
		return false;
	}
	
	try
	{
		int height = stoi(hgt.substr(0,hgt.size() - 2));
		return (height >= min && height <= max);
	}
	catch (...)
	{
		return false;
	}
}

bool Passport::HairColorIsValid()
{
	if (hcl.size() != 7 || hcl[0] != '#')
	{
		return false;
	}
	
	string hairColor = hcl.substr(1, 6);

	for (int i = 1; i < hcl.size(); i++)
	{
		if ((hairColor[i] >= '0' && hairColor[i] <= '9') || (hairColor[i] >= 'a' && hairColor[i] <= 'f'));
	}
}

bool Passport::EyeColorIsValid()
{
	vector<string> color = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
	
	for (string c : color)
	{
		if (ecl == c)
		{
			return true;
		}
	}

	return false;
}

bool Passport::PassportIDIsValid()
{
	if (pid.size() != 9)
	{
		return false;
	}

	try
	{
		int n = stoi(pid);
	}
	catch (...)
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
		return 0;
	}

	string inputLine;
	string inputPassport;
	int count = 0;

	while (getline(input, inputLine))
	{
		if (inputLine.empty())
		{
			Passport passport;

			passport.CreatePassport(inputPassport);
			inputPassport.clear();

			if (passport.IsValid())
			{
				count++;
			}
			continue;
		}

		inputPassport = inputLine + " " + inputPassport;
	}

	Passport passport;
	passport.CreatePassport(inputPassport);

	if (passport.IsValid())
	{
		count++;
	}

	cout << count << " passports are valid." << endl;

	return 0;
}


