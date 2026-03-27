#pragma once

#include "BaseCharacter.h"
#include "Inventory.h"

class PlayerManager : public BaseCharacter
{
public:
    int GetLevel();
    int GetExperience();
    int GetMaxExperience();
    int GetDexterity();
    int GetIntelligence();
    int GetLuck();
    int GetCriticalProbability();
    int GetGold();

    void SetLevel(int Level);
    void SetExperience(int Experience);
    void SetMaxExperience(int MaxExperience);
    void SetDexterity(int Dexterity);
    void SetIntelligence(int Intelligence);
    void SetLuck(int Luck);
    void SetCriticalProbability(int CriticalProbability);
    void SetGold(int Gold);

    void CollectItem(shared_ptr<ItemManager> Item);
    void UseItem(const string& ItemName, PlayerManager* Player);
    bool RemoveItem(const string& ItemName);
    void ShowItems();

    shared_ptr<ItemManager> FindItem(const string& ItemName);

    void PrintPlayerStatus();

private:
    int Level = 0;
    int Experience = 0;
    int MaxExperience = 100;
    int Dexterity = 0;
    int Intelligence = 0;
    int Luck = 0;
    int CriticalProbability = 0;
    int Gold = 0;

    Inventory PlayerInventory;
};
