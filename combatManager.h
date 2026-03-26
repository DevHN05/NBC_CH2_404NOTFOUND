#pragma once
#include <iostream>

using namespace std;

class character;

class combatManager
{
private:
    combatManager() {}

public:
    combatManager(const combatManager&) = delete;
    void operator=(const combatManager&) = delete;

    static combatManager& get_instance()
    {
        static combatManager instance;
        return instance;
    }

public:
    void start_battle(character& player, character& monster);

    void update_battle_ui(character& player, character& monster);

    int random_dice(int dice);

    void reward(character& player);

};