#pragma once
#include "Monster.h"

struct Point
{
	int x;
	int y;
};

class Map
{
private:
	Point player_position{};
public:
	Map();
	Point get_player_position() const;
	void move_player();
	void print_player_position() const;
	static Actor* generate_monster();
};