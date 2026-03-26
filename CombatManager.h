#pragma once
#include <iostream>
#include "DiceSystem.h"

using namespace std;

class BaseCharacter;

class CombatManager
{
private:
    CombatManager() {}

    DiceSystem Dice;

public:
    CombatManager(const CombatManager&) = delete;
    void operator=(const CombatManager&) = delete;

    static CombatManager& GetInstance()
    {
        static CombatManager Instance;
        return Instance;
    }

public:
    void StartBattle(BaseCharacter& Player, BaseCharacter& Monster);

    void UpdateBattleUI(BaseCharacter& Player, BaseCharacter& Monster);

    void UpdateStoreUI(BaseCharacter& Player);

    void UpdateEventUI(BaseCharacter& Player);

    void Reward(BaseCharacter& Player);

};
