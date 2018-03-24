#include "Player.h"
#include "Engine.h"

using std::cout;
using std::cin;
using std::endl;

const auto level_experience = 100u;

Player::Player()
{
}

void Player::generate_player()
{
	cout << "CHARACTER CREATION" << endl;
	cout << "******************" << endl;

	cout << "What is your champion's name? ";
	cin >> name;

	char player_class;
	cout << "Select the character class you want to become: " << endl;
	cout << "(B)arbarian, (M)age, (D)ruid, (R)ogue: ";
	cin >> player_class;

	Weapon weapon;

	switch(player_class)
	{
	case 'b':
	case 'B':
		set_class("Barbarian");
		set_accuracy(10u);
		set_hitpoint(15);
		set_initiative(11u);
		maximum_hitpoints = get_hitpoints();
		experience_needed = level_experience;
		level = 1u;
		set_armour(2u);
		weapon.name = "Great Axe";
		weapon.damage_die = 8u;
		break;
	case 'M':
	case 'm':
		set_class("Mage");
		set_accuracy(5u);
		set_hitpoint(8);
		set_initiative(10u);
		maximum_hitpoints = get_hitpoints();
		experience_needed = level_experience;
		level = 1u;
		set_armour(2u);
		weapon.name = "Staff";
		weapon.damage_die = 4u;
		break;

	case 'D':
	case 'd':
		set_class("Druid");
		set_accuracy(7u);
		set_hitpoint(12);
		set_initiative(10u);
		maximum_hitpoints = get_hitpoints();
		experience_needed = level_experience;
		level = 1u;
		set_armour(3u);
		weapon.name = "Mace";
		weapon.damage_die = 6u;
		break;

	case 'R':
	case 'r':
		set_class("Rogue");
		set_accuracy(12u);
		set_hitpoint(10);
		set_initiative(16u);
		maximum_hitpoints = get_hitpoints();
		experience_needed = level_experience;
		level = 1u;
		set_armour(2u);
		weapon.name = "Dagger";
		weapon.damage_die = 4u;
		break;
	}

	set_weapon(weapon);
}

void Player::heal()
{
	cout << "You have set up camp..." << endl;
	set_hitpoint(maximum_hitpoints);
}

void Player::print_stats()
{
	cout << endl << get_description() << "'s Condition" << endl;
	cout << "*********************" << endl;

	cout << "\tClass is " << get_class() << endl;
	cout << "\tYour initiative is " << get_initiative() << endl;
	cout << "\tYour accuracy is " << get_accuracy() << endl;
	cout << "\tYour armour is " << get_armour() << endl;
	cout << "\tYour current HP is " << get_hitpoints() << endl;
	cout << "\tYour max HP is " << maximum_hitpoints << endl;
	cout << "\tYour current experience is " << get_experience() << endl;
	cout << "\tExperience needed for level up " << experience_needed << endl;
	cout << "\tYour current level is " << level << endl;
	cout << "\tYour weapon is " << get_weapon().name << "(D" 
		<< get_weapon().damage_die << ")" << endl << endl;
}

bool Player::perform_action(Actor* actor) const
{
	// prompt the player to do the following:
	//  Attack
	//  Retreat
	char input;
	cout << endl << "A)ttack, R)etreat: ";
	cin >> input;

	int roll{}, damage{};

	switch(input)
	{
	case 'a':
	case 'A':

		cout << "You attacked the " << actor->get_class()
			<< " with your " << get_weapon().name << " (D"
			<< get_weapon().damage_die << ")" << endl;

		// check if player hits monster
		roll = roll_dice(1, 20);

		// Hit the monster
		if (roll > get_accuracy())
		{
			cout << "\tYour swing missed the monster!" << endl;
			break;
		}

		// Determine damage done to monster
		roll = roll_dice(1, get_weapon().damage_die);

		// Take into account monster's armour
		damage = roll - actor->get_armour();

		// If roll <= 0 the monster must take at least one damage
		damage = (damage <= 0) ? 1 : damage;

		cout << "\tYour attack did " << damage << " damage." << endl;

		actor->do_damage(damage);

		break;

	case 'r':
	case 'R':

		return true;
	}

	return false;

}

std::string Player::get_description() const
{
	return name;
}

void Player::assign_experience(const unsigned int experience)
{
	//LV1 ->  3
	// 99 + 102 = 201
	const auto temp_exp = get_experience() + experience;
	set_experience(temp_exp);
}

void Player::level_check()
{
	auto still_leveling = true;
	while (still_leveling) {

		if (get_experience() <= experience_needed)
		{
			return;
		}

		cout << "Congratulations! You have leveled up!" << endl;

		set_accuracy(get_accuracy() + roll_dice(0, 1));
		set_armour(get_armour() + roll_dice(0, 1));
		maximum_hitpoints += roll_dice(1, 3);
		set_hitpoint(maximum_hitpoints);
		level++;

		auto current_experience = (level - 1) * level_experience;

		still_leveling = (level * level_experience) - get_experience() 
			>= level_experience;
			
		experience_needed = level_experience * level;
	}
}