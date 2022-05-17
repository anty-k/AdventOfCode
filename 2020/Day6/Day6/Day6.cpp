#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string ListGroupAnswers(string inputLine, string answers)
{
	return answers + inputLine; 
}

int CountAnswers(string rawAnswers, int groupSize)
{
	sort(rawAnswers.begin(), rawAnswers.end());

	string sortedAnswers = rawAnswers;
	int count = 0;

	for (int i = 0; i < sortedAnswers.size(); i++)
	{
		if (i == sortedAnswers.size() - 1 || sortedAnswers[i] != sortedAnswers[i + 1])
		{
			int begin = sortedAnswers.find_first_of(sortedAnswers[i]);
			int end = sortedAnswers.find_last_of(sortedAnswers[i]) + 1;

			int answerLength = end - begin;

			if (answerLength == groupSize)
			{
				count++;
			}
		}
	}

	return count;
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
	string rawAnswers;

	int groupSize = 0, count = 0;

	while (getline(input, inputLine))
	{
		rawAnswers = ListGroupAnswers(inputLine, rawAnswers);

		if (inputLine.empty())
		{
			count = count + CountAnswers(rawAnswers, groupSize);
			rawAnswers = "";
			groupSize = 0;

			continue;
		}

		groupSize++;
	}

	count = count + CountAnswers(rawAnswers, groupSize);

	cout << "The total count is " << count << endl;

	return 0;
}