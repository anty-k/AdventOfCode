#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Bag {
public:
	string color;
	map<string, int> ruleSet;

public: 
	void FindBagColor(string inputLine);
	void FindBagRule(string inputLine);
	bool ContainShinyGold(const vector<Bag>& allRules) const;
	int CountRequiredBags(const vector<Bag>& allRules) const;
};

void Bag::FindBagColor(string inputLine)
{
	int end = inputLine.find("bags");
	color = inputLine.substr(0, end - 1);
}

void Bag::FindBagRule(string inputLine)
{
	int begin = inputLine.find("contain") + string("contain ").size();
	int end;

	while(inputLine.find("bag", begin) != string::npos)
	{
		end = inputLine.find("bag", begin + 1);
		string unitColorRule = inputLine.substr(begin, end - begin - 1);

		if (unitColorRule == "no other") break;

		int sepPos = unitColorRule.find(" ");
		string count = unitColorRule.substr(0, sepPos);
		string color = unitColorRule.substr(sepPos + 1);

		this->ruleSet[color] = stoi(count);

		begin = inputLine.find_first_of(",.", end);
		if (begin == inputLine.size() - 1) {
			break;
		}

		begin += 2;
	}
}

bool Bag::ContainShinyGold(const vector<Bag>& allRules) const
{
	for (const pair<string, int>& kvPair : this->ruleSet)
	{
		string key = kvPair.first;
		int value = kvPair.second;

		if (key == "shiny gold")
		{
			return true;
		}
		
		const Bag* subRule = nullptr;
		for (int i = 0; i < allRules.size(); i++)
		{
			if (allRules[i].color == key) {
				subRule = &allRules[i];
				break;
			}
		}

		if (subRule == nullptr) 
		{
			continue; // not found
		}

		if (subRule->ContainShinyGold(allRules))
		{
			return true;
		}
	}

	return false;
}

int Bag::CountRequiredBags(const vector<Bag>& allRules) const
{
	int bagCount = 1;
	for (const pair<string, int>& kvPair : this->ruleSet)
	{
		string key = kvPair.first;
		int value = kvPair.second;

		if (key == "") continue;

		for (int i = 0; i < allRules.size(); i++)
		{
			if (key == allRules[i].color)
			{
				bagCount += value * (allRules[i].CountRequiredBags(allRules));
				break;
			}
		}
	}

	return bagCount;
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
	vector<Bag> ruleSet;
	int count = 0;

	while (getline(input, inputLine))
	{
		Bag bag;
		bag.FindBagColor(inputLine);
		bag.FindBagRule(inputLine);

		ruleSet.push_back(bag);

		cout << bag.color << ": ";

		for (const pair<string, int>& kvPair : bag.ruleSet)
		{
			cout << kvPair.first << ", ";
		}

		cout << endl;
	}

	for (int i = 0; i < ruleSet.size(); i++)
	{
		if (ruleSet[i].ContainShinyGold(ruleSet))
		{
			count++;
		}
	}

	cout << count << " bags can contain a shiny gold bag." << endl;

	for (int i = 0; i < ruleSet.size(); i++)
	{
		if (ruleSet[i].color == "shiny gold")
		{
			int bagCount = ruleSet[i].CountRequiredBags(ruleSet);
			cout << "The shiny gold bag must contain " << bagCount << " bags." << endl;
		}
	}
}
