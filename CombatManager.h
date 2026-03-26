#pragma once
#include <iostream>

using namespace std;

class BaseCharacter;

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
    void StartBattle(BaseCharacter& Player, BaseCharacter& Monster);

    void UpdateBattleUI(BaseCharacter& Player, BaseCharacter& Monster);

    void Reward(BaseCharacter& Player);

};
