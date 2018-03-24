#include "Map.h"
#include <iostream>
#include "Engine.h"
#include "Weapon.h"

using std::cout;
using std::cin;
using std::endl;

Map::Map()
{
	player_position.x = 0;
	player_position.y = 0;
}

Point Map::get_player_position() const
{
	return player_position;
}

void Map::move_player()
{
	char input;
	cout << "N)orth, S)outh, E)ast, W)est: ";
	cin >> input;
	cout << endl;

	switch (input)
	{
	case 'n':
	case 'N':
		player_position.y++;
		return;

	case 's':
	case 'S':
		player_position.y--;
		return;
	case 'e':
	case 'E':
		player_position.x++;
		return;
	case 'w':
	case 'W':
		player_position.x--;
		return;
	}
}

void Map::print_player_position() const
{
	cout << "The player is at x = " << player_position.x
		<< " y = " << player_position.y << endl << endl;
}

Actor* Map::generate_monster()
{
	const int roll = roll_dice(1, 20);
	Monster* monster = nullptr;

	if(roll <= 5)
	{
		monster = nullptr;
	}
	else if(roll <= 10)
	{
		monster = new Monster("Rat");
	}
	else if(roll <= 15)
	{
		monster = new Monster("Goblin");
	}
	else if(roll <= 19)
	{
		monster = new Monster("Scorpion");
	}
	else
	{
		monster = new Monster("Dragon");
	}

	return monster;

}
