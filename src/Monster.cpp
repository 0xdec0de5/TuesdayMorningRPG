#include "Monster.h"
#include "Player.h"
#include <iostream>
#include "Engine.h"

using std::cout;
using std::endl;

Monster::Monster(const std::string& type)
{
	Weapon weapon;
	unsigned int accuracy{};
	int hitpoints{};
	unsigned int armour{};
	unsigned int experience{};
	unsigned int initiative{};

	if (type == "Rat")
	{
		weapon.name = "Bite";
		weapon.damage_die = 4u;

		accuracy = 12u;
		hitpoints = 4;
		armour = 1u;
		experience = 20u;
		initiative = 16u;
	}

	if (type == "Goblin")
	{
		weapon.name = "Sword";
		weapon.damage_die = 6u;

		accuracy = 10u;
		hitpoints = 8;
		armour = 3u;
		experience = 40u;
		initiative = 12u;
	}

	if (type == "Scorpion")
	{
		weapon.name = "Stinger";
		weapon.damage_die = 8u;

		accuracy = 8u;
		hitpoints = 10;
		armour = 4u;
		experience = 80u;
		initiative = 8u;
	}

	if (type == "Dragon")
	{
		weapon.name = "Fire Breath";
		weapon.damage_die = 10u;

		accuracy = 8u;
		hitpoints = 25;
		armour = 6u;
		experience = 200u;
		initiative = 10u;
	}

	set_class(type);
	set_weapon(weapon);
	set_hitpoint(hitpoints);
	set_accuracy(accuracy);
	set_armour(armour);
	set_experience(experience);
	set_initiative(initiative);

	print_stats();
}

bool Monster::perform_action(Actor* player) const
{
	cout << "The monster attacks " << player->get_description() << endl;

	auto roll = roll_dice(1, 20);

	if (roll > get_accuracy())
	{
		cout << "\tThe " << get_description() << " misses!" << endl;
		return false;
	}

	// Determine damage done to monster
	roll = roll_dice(1, get_weapon().damage_die);

	// Take into account monster's armour
	int damage = roll - player->get_armour();

	// If roll <= 0 the target must take at least one damage
	damage = (damage <= 0) ? 1 : damage;

	cout << "\tMonster's attack did " << damage << " damage." << endl;

	player->do_damage(damage);

	return false;
}

void Monster::print_stats()
{
	cout << endl << get_description() << "'s Condition" << endl;
	cout << "*********************" << endl;

	cout << "\tInitiative is " << get_initiative() << endl;
	cout << "\tAccuracy is " << get_accuracy() << endl;
	cout << "\tArmour is " << get_armour() << endl;
	cout << "\tCurrent HP is " << get_hitpoints() << endl;
	cout << "\tExperience points given " << get_experience() << endl;
	cout << "\tWeapon is " << get_weapon().name << "(D" 
		<< get_weapon().damage_die << ")" << endl << endl;
}
