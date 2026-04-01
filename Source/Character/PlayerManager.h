#pragma once

#include "BaseCharacter.h"
#include "../Item/Inventory.h"
#include "../BasicSystem/DiceSystem.h"

class BaseItem;

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
    Inventory& GetPlayerInventory();

    void SetLevel(int Level);
    void SetExperience(int Experience);
    void SetMaxExperience(int MaxExperience);
    void SetDexterity(int Dexterity);
    void SetIntelligence(int Intelligence);
    void SetLuck(int Luck);
    void SetCriticalProbability(int CriticalProbability);
    void SetGold(int Gold);

    void CollectItem(std::unique_ptr<BaseItem> Item);
    void UseItem(const string& ItemName);
    void RemoveItem(const string& ItemName);
    //void ShowItems();

    void LevelUp();
    BaseItem* FindItem(const string& ItemName);

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

    DiceSystem Dice;

    Inventory PlayerInventory;
};
