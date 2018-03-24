#pragma once
#include <string>
#include "Weapon.h"

class Actor
{
private:
	unsigned int accuracy;
	unsigned int initiative{0u};
	unsigned int armour_rating;
	unsigned int experience_points{0u};
	int current_hitpoints;
	std::string actor_class;
	Weapon weapon;

protected:
	void set_weapon(Weapon weapon);
	void set_class(std::string actor_class);
	void set_hitpoint(int hitpoints);
	void set_accuracy(unsigned int accuracy);
	void set_armour(unsigned int armour);
	void set_experience(unsigned int experience);
	void set_initiative(unsigned int initiative);

public:
	bool is_defeated() const;
	virtual std::string get_description() const;
	Weapon get_weapon() const;
	std::string get_class() const;
	int get_hitpoints() const;
	unsigned int get_accuracy() const;
	unsigned int get_armour() const;
	unsigned int get_experience() const;
	unsigned int get_initiative() const;
	void do_damage(unsigned int damage);
	virtual void print_stats();
	virtual bool perform_action(Actor* actor) const;
	virtual void assign_experience(const unsigned int experience);
	virtual void level_check();
};
