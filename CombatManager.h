#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "DiceSystem.h"

using namespace std;

class PlayerManager;
class BaseMonster;

class CombatManager
{
private:
    CombatManager() {};

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

    void UpdateBattleUI(PlayerManager& Player, BaseMonster& Monster);
    void UpdateStoreUI(PlayerManager& Player);
    void UpdateEventUI(PlayerManager& Player);


    void Reward(PlayerManager& Player);
    void UpdateStore();

};
