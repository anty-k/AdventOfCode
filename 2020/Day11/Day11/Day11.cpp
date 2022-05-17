#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

bool AdjacentSeatOccupied(const vector<vector<char>>& room, int i, int j)
{
	// For Part 2 - in progress
	/*for (int k = 1; k < room[i].size() - 1; k++)
	{
		if (room[i][k] == '#' && k != j) return true;
	}

	for (int k = 1; k < room.size() - 1; k++)
	{
		if (room[k][j] == '#' && k != i) return true;
	}

	for (int k = 1; k < minDimension - 1; k++)
	{
		if (room[i + k][j + k] == '#') return true;
	}

	for (int k = 1; k < room[i].size() - 1; k++)
	{
		if (room[k][j] == '#') return true;
	}*/
	
	if (room[i + 1][j] == '#' || room[i - 1][j] == '#'
		|| room[i][j + 1] == '#' || room[i][j - 1] == '#'
		|| room[i + 1][j + 1] == '#' || room[i + 1][j - 1] == '#'
		|| room[i - 1][j + 1] == '#' || room[i - 1][j - 1] == '#')
	{
		return true;
	}

	return false;
}

bool NoAdjacentEmptySeat(const vector<vector<char>>& room, int i, int j)
{
	int occupiedSeats = 0;

	for (int k : {i, i + 1, i - 1})
		for (int l : {j, j + 1, j - 1})
		{
			if (k == i && l == j) continue;

			if (room[k][l] == '#') occupiedSeats++;
		}

	if (occupiedSeats >= 5) return true;

	return false;
}

vector<vector<char>> updateRoom(const vector<vector<char>>& room)
{
	vector<vector<char>> updatedRoom = room;

	char emptySeat = 'L';
	char floor = '.';
	char occupiedSeat = '#';

	for (int i = 0; i < room.size(); i++)
	{
		for (int j = 1; j < room[i].size() - 1; j++)
		{
			if (room[i][j] == floor || room[i][j] == '_' || room[i][j] == '|')
			{
				updatedRoom[i][j] = room[i][j];
			}

			if (room[i][j] == emptySeat)
			{
				if (!AdjacentSeatOccupied(room, i, j))
				{
					updatedRoom[i][j] = occupiedSeat;
				}
				else
				{
					updatedRoom[i][j] = emptySeat;
				}
			}

			if (room[i][j] == occupiedSeat)
			{
				if (NoAdjacentEmptySeat(room, i , j))
				{
					updatedRoom[i][j] = emptySeat;
				}
				else
				{
					updatedRoom[i][j] = occupiedSeat;
				}
			}

			cout << updatedRoom[i][j];
		}
		cout << endl;
	}

	return updatedRoom;
}

bool HasConverged(const vector<vector<char>>& room, const vector<vector<char>>& updatedRoom)
{
	if (updatedRoom == room) return true;

	return false;
}

void AddWalls(vector<vector<char>>& room)
{
	vector<char> horizontalWall(room[0].size());

	for (int i = 0; i < horizontalWall.size(); i++)
	{
		horizontalWall[i] = '_';
	}

	room.insert(room.begin(), horizontalWall);
	room.push_back(horizontalWall);
	
	room[0].insert(room[0].begin(), ' ');
	room[0].push_back(' ');

	for (int i = 1; i < room.size(); i++)
	{
		room[i].insert(room[i].begin(), '|');
		room[i].push_back('|');
	}
}

int CountOccupiedSeats(vector<vector<char>> room)
{
	int count = 0;

	for(int i = 0; i < room.size(); i++)
		for (int j = 0; j < room[i].size(); j++)
		{
			if (room[i][j] == '#') count++;
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
	vector<vector<char>> currentRoom; 
	int i = 0;

	while (getline(input, inputLine))
	{
		currentRoom.resize(i + 1);
		for (int j = 0; j < inputLine.size(); j++)
		{
			currentRoom[i].push_back(inputLine[j]);
		}
		i++;
	}

	AddWalls(currentRoom);

	for (int i = 0; i < currentRoom.size(); i++)
	{
		for (int j = 0; j < currentRoom[i].size(); j++)
		{
			cout << currentRoom[i][j];
		}
		cout << endl;
	}

	

	vector<vector<char>> updatedRoom = updateRoom(currentRoom);

	while (!HasConverged(currentRoom, updatedRoom))
	{
		cout << endl;
		
		currentRoom = updatedRoom;
		updatedRoom = updateRoom(updatedRoom);
	}

	cout << "The room end up with " << CountOccupiedSeats(updatedRoom) << " occupied seats." << endl;

}
