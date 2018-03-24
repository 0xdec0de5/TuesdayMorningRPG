#include "Actor.h"

bool Actor::is_defeated() const
{
	return current_hitpoints <= 0;
}

bool Actor::perform_action(Actor* actor) const
{
	return false;
}

void Actor::assign_experience(const unsigned int experience)
{

}

void Actor::level_check()
{
}

void Actor::print_stats()
{

}

void Actor::do_damage(unsigned int damage)
{
	current_hitpoints -= damage;
}


void Actor::set_weapon(Weapon weapon)
{
	this->weapon = weapon;
}

void Actor::set_class(std::string actor_class)
{
	this->actor_class = actor_class;
}

void Actor::set_hitpoint(int hitpoints)
{
	this->current_hitpoints = hitpoints;
}

void Actor::set_accuracy(unsigned int accuracy)
{
	this->accuracy = accuracy;
}

void Actor::set_armour(unsigned int armour)
{
	armour_rating = armour;
}

void Actor::set_experience(unsigned int experience)
{
	this->experience_points = experience;
}

void Actor::set_initiative(unsigned int initiative)
{
	this->initiative = initiative;
}

std::string Actor::get_description() const
{
	return get_class();
}

Weapon Actor::get_weapon() const
{
	return weapon;
}

int Actor::get_hitpoints() const
{
	return current_hitpoints;
}

unsigned Actor::get_accuracy() const
{
	return accuracy;
}

unsigned Actor::get_armour() const
{
	return armour_rating;
}

unsigned Actor::get_experience() const
{
	return experience_points;
}

unsigned Actor::get_initiative() const
{
	return initiative;
}

std::string Actor::get_class() const
{
	return actor_class;
}
