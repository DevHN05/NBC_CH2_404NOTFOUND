#pragma once

#include "BaseCharacter.h"
#include "Inventory.h"

class ItemManager;

class PlayerManager : public BaseCharacter
{
public:
    PlayerManager(string Nickname);

    int GetLevel() const;
    int GetExperience() const;
    int GetMaxExperience() const;
    int GetDexterity() const;
    int GetIntelligence() const;
    int GetLuck() const;
    int GetCriticalProbability() const;
    int GetGold() const;
    const vector<unique_ptr<ItemManager>>& GetPlayerInventory() const;

    void SetLevel(int Level);
    void SetExperience(int Experience);
    void SetMaxExperience(int MaxExperience);
    void SetDexterity(int Dexterity);
    void SetIntelligence(int Intelligence);
    void SetLuck(int Luck);
    void SetCriticalProbability(int CriticalProbability);
    void SetGold(int Gold);

    void CollectItem(std::unique_ptr<ItemManager> Item);
    void UseItem(const string& ItemName);
    void RemoveItem(const string& ItemName);
    //void ShowItems();

    ItemManager* FindItem(const string& ItemName);

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
