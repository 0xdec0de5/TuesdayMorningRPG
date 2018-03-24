#pragma once

#include <string>
#include <iostream>
#include "Actor.h"

class Player : public Actor
{
private:
	std::string name;
	int maximum_hitpoints;

	unsigned int experience_needed;
	unsigned int level;


public:
	Player();

	void generate_player();
	void heal();
	void print_stats() override;
	bool perform_action(Actor* actor) const override;
	std::string get_description() const override;
	void assign_experience(const unsigned experience) override;
	void level_check() override;
};
