#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class Ship {
public:
	int xPosition;
	int yPosition;
	int direction;

	void Move(char direction, int position);
	Ship(int xPosition = 0, int yPosition = 0, int direction = 90);
};

Ship::Ship(int xPosition, int yPosition, int direction)
{
	this->xPosition = xPosition;
	this->yPosition = yPosition;
	this->direction = direction;
}

void Ship::Move(char direction, int position)
{
	switch (direction) {
	case 'N':
		this->yPosition += position;
		break;

	case 'S':
		this->yPosition -= position;
		break;

	case 'E':
		this->xPosition += position;
		break;

	case 'W':
		this->xPosition -= position;
		break;

	case 'L':
		this->direction -= position;
		if (this->direction < 0)
		{
			this->direction += 360;
		}
		break;

	case 'R':
		this->direction += position;
		if (this->direction >= 360)
		{
			this->direction -= 360;
		}
		break;

	case 'F':
		if (this->direction == 0)
		{
			this->yPosition += position;
		}
		else if (this->direction == 180)
		{
			this->yPosition -= position;
		}
		else if (this->direction == 90)
		{
			this->xPosition += position;
		}
		else if (this->direction == 270)
		{
			this->xPosition -= position;
		}
		break;
	}

	return;
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
	Ship ship;

	while (getline(input, inputLine))
	{
		char direction = inputLine[0];
		int position = stoi(inputLine.substr(1, inputLine.size() - 1));

		ship.Move(direction, position);
	}

	cout << abs(ship.xPosition) + abs(ship.yPosition) << endl;
}
