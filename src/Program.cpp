#include <iostream>
#include "Player.h"
#include "Map.h"
#include "Engine.h"

using std::cout;
using std::cin;
using std::endl;

bool is_player_defeated(Player* player, Actor* monster)
{
	if(player->is_defeated())
	{
		cout << "You have been defeated by a " << monster->get_class()
			<< " RIP " << player->get_description() << endl;
		return true;
	}
	return false;
}

bool do_attack(Player* player)
{
	auto monster = Map::generate_monster();
	auto has_retreated = false;
	auto is_game_over = false;

	if (monster == nullptr)
	{
		return is_game_over;
	}

	//we got a monster - do init check
	const int d_initiative = player->get_initiative() 
		- monster->get_initiative();
	const int roll = roll_dice(1, 20) - d_initiative;

	Actor* attacker = monster;
	Actor* defender = player;

	if (roll <= 10)
	{
		//monster wins initiative
		attacker = player;
		defender = monster;
	}

	// do perform_action phase
	while (!has_retreated)
	{
		// attcker perform_action
		has_retreated = attacker->perform_action(defender);

		if (defender->is_defeated())
		{
			if(is_player_defeated(player, monster))
			{
				is_game_over = true;
				break;
			}

			// player was successful & gets exp.
			const auto exp = defender->get_experience();
			attacker->assign_experience(exp);
			attacker->level_check();
			break;
		}
		else
		{
			defender->print_stats();
		}

		// Defenders's turn
		has_retreated |= defender->perform_action(attacker);

		if (attacker->is_defeated())
		{
			if (is_player_defeated(player, monster))
			{
				is_game_over = true;
				break;
			}

			const auto exp = defender->get_experience();
			attacker->assign_experience(exp);
			attacker->level_check();
			break;
		}
		else
		{
			attacker->print_stats();
		}
	}

	delete monster;
	defender = attacker = nullptr;

	return is_game_over;
}

int main()
{
	auto player = new Player();
	player->generate_player();
	player->print_stats();

	Map map;

	// Create game loop
	auto is_game_over = false;

	while (!is_game_over)
	{
		// Print player position in dungeon
		map.print_player_position();

		// Prompt & Accept player action
		char input;
		cout << "M)ove, C)amp, V)iew stats, Q)uit: ";
		cin >> input;


		switch (input)
		{
		case 'm':
		case 'M':

			map.move_player();
			is_game_over = do_attack(player);

			break;

		case 'c':
		case 'C':

			is_game_over = do_attack(player);
			player->heal();
			break;

		case 'v':
		case 'V':
			player->print_stats();
			break;

		case 'q':
		case 'Q':
			is_game_over = true;
			break;

		}
	}

	return 0;
}
