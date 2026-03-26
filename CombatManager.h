#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "DiceSystem.h"

using namespace std;

class BaseCharacter;

class CombatManager
{
private:
    CombatManager() {};

    DiceSystem Dice;
    unordered_map<string, int> TotalItems; // 전체 아이템 데이터베이스
    vector<pair<string, int>> CurrentShopList; // 현재 상점에 진열된 목록


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
    void UpdateStore();

};
