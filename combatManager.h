#pragma once
#include <iostream>

using namespace std;

class character;

class CombatManager
{
private:
    CombatManager() {}

public:
    CombatManager(const CombatManager&) = delete;
    void operator=(const CombatManager&) = delete;

    static CombatManager& GetInstance()
    {
        static CombatManager Instance;
        return Instance;
    }

public:
    void StartBattle(character& Player, character& Monster);

    void UpdateBattleUI(character& Player, character& Monster);

    void Reward(character& Player);

};
