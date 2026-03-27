#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "DiceSystem.h"

using namespace std;

class PlayerManager;
class BaseMonster;
class BaseBossMonster;

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
    void StartBattle(PlayerManager& Player, BaseMonster& Monster);
    void StartBossBattle(PlayerManager& Player, BaseBossMonster& Boss);

    void UpdateBattleUI(PlayerManager& Player, BaseMonster& Monster);
    void UpdateStoreUI(PlayerManager& Player);
    void UpdateEventUI(PlayerManager& Player, BaseMonster& Monster);

    void Reward(PlayerManager& Player, BaseMonster& Monster);
};
