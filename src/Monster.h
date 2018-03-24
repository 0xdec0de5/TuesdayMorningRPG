#pragma once
#include <string>
#include "Weapon.h"
#include "Actor.h"

class Monster : public Actor
{
private:

public:
	explicit Monster(const std::string& type);
	bool perform_action(Actor* actor) const override;
	void print_stats() override;
};
