#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int JoltageDiff(int adapter, int joltage)
{
	int diff = adapter - joltage;
	
	if (diff == 1) return 1;
	else if (diff == 2) return 2;
	else if (diff == 3) return 3;

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
	vector<int> adapterList;

	while (getline(input, inputLine))
	{
		int joltage = stoi(inputLine);
		adapterList.push_back(joltage);
	}

	sort(adapterList.begin(), adapterList.end());

	int joltage = 0;
	int diff1 = 0, diff2 = 0, diff3 = 0;
	int arrangementCount = 0;

	for (int i = 0; i < adapterList.size(); i++)
	{
		if (JoltageDiff(adapterList[i], joltage) == 1)
		{
			joltage += 1;
			diff1++;
		}
		else if (JoltageDiff(adapterList[i], joltage) == 2)
		{
			joltage += 2;
			diff2++;
		}
		else if (JoltageDiff(adapterList[i], joltage) == 3)
		{
			joltage += 3;
			diff3++;
		}
		else
		{
			cout << "No adapters matching." << endl;
		}

		if (i < adapterList.size() - 1)
		{
			arrangementCount += OtherArrangementsCount(adapterList, i);
		}

	}

	for (int i = 0; i < adapterList.size(); i++)
	{
		cout << adapterList[i] << endl;
	}

	diff3++;

	cout << "There are " 
		<< diff1 << " differences of 1 Jolt, "
		<< diff2 << " differences of 2 Jolt and "
		<< diff3 << " differences of 3 Jolt." << endl;

	cout << endl;

	cout << "The product is " << diff1 * diff3 << endl;

	cout << arrangementCount << " possible arrangements." << endl;
}
