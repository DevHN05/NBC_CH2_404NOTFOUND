#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "DiceSystem.h"

using namespace std;

class PlayerManager;
class MonsterManager;

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
    void StartBattle(PlayerManager& Player, MonsterManager& Monster);

    void UpdateBattleUI(PlayerManager& Player, MonsterManager& Monster);
    void UpdateStoreUI(PlayerManager& Player);
    void UpdateEventUI(PlayerManager& Player);


    void Reward(PlayerManager& Player);
    void UpdateStore();

};
