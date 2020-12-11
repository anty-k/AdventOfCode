#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class Instruction
{
public:
	string action;
	int value;

public:
	void ReadInstruction(string inputLine);
};

void Instruction::ReadInstruction(string inputLine)
{	
	int separator = inputLine.find(" ");

	this->action = inputLine.substr(0, separator);
	this->value = stoi(inputLine.substr(separator + 1));
}

bool HasLooped(int i, const vector<int>& list)
{
	for (int j = 0; j < list.size(); j++)
	{
		if (list[j] == i) return true;
	}

	return false;
}

pair<int, int> ExecuteInstruction(const vector<Instruction>& instructions, int currentPosition)
{
	pair<int, int> posAcc;

	if (instructions[currentPosition].action == "nop")
	{
		posAcc.first = 1;
		posAcc.second = 0;
	}
	else if (instructions[currentPosition].action == "jmp")
	{
		if (instructions[currentPosition].value == 0)
		{
			posAcc.first = 1;
			posAcc.second = 0;
		}
		else
		{
			posAcc.first = instructions[currentPosition].value;
			posAcc.second = 0;
		}
	}
	else if (instructions[currentPosition].action == "acc")
	{
		posAcc.first = 1;
		posAcc.second = instructions[currentPosition].value;
	}

	return posAcc;
}

Instruction Repair(Instruction unitInstruction)
{
	if (unitInstruction.action == "nop")
	{
		unitInstruction.action = "jmp";
	}
	else if (unitInstruction.action == "jmp")
	{
		unitInstruction.action = "nop";
	}

	return unitInstruction;
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
	vector<Instruction> instructions;

	while (getline(input, inputLine))
	{
		Instruction unitInstruction;
		unitInstruction.ReadInstruction(inputLine);

		instructions.push_back(unitInstruction);
	}

	for (int i = 0; i < instructions.size(); i++)
	{
		cout << instructions[i].action << ", " << instructions[i].value << endl;
	}

	int acc;

	for (int j = 0; j < instructions.size(); j++)
	{
		int i = 0;
		acc = 0;
		vector<int> positionList;
		vector<Instruction> repairedInstructions = instructions;

		if (repairedInstructions[j].action == "nop" || repairedInstructions[j].action == "jmp")
		{
			repairedInstructions[j] = Repair(repairedInstructions[j]);
		}
		else continue;
		
		cout << "     " << j << endl;

		while (!HasLooped(i, positionList))
		{
			pair<int, int> posAcc;

			if (i >= repairedInstructions.size() || i < 0) break;

			positionList.push_back(i);

			cout << i << ", " << acc << endl;

			posAcc = ExecuteInstruction(repairedInstructions, i);

			i += posAcc.first;
			acc += posAcc.second;
		}

		if (i >= repairedInstructions.size()) break;
	}

	cout << "The accumulator value is " << acc << endl;
}

