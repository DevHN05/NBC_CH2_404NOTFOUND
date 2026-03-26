#pragma once
#include <iostream>

using namespace std;

class BaseCharacter
{
public:
    BaseCharacter(string Nickname);

    virtual ~BaseCharacter() = default;

    string GetNickname() const;
    int GetLevel() const;
    int GetExperience() const;
    int GetHealth() const;
    int GetMaxHealth() const;
    int GetStrength() const;
    int GetDexterity() const;
    int GetIntelligence() const;
    int GetLuck() const;
    int GetCriticalProbability() const;
    int GetGold() const;

    void SetNickname(string Nickname);
    void SetLevel(int Level);
    void SetExperience(int Experience);
    void SetHealth(int Health);
    void SetMaxHealth(int MaxHealth);
    void SetStrength(int Strength);
    void SetDexterity(int Dexterity);
    void SetIntelligence(int Intelligence);
    void SetLuck(int Luck);
    void SetCriticalProbability(int CriticalProbability);
    void SetGold(int Gold);

    void PrintCharacterStatus();

private:
    string Nickname = " ";
    int Level = 0;
    int Experience = 0;
    int Health = 0;
    int MaxHealth = 0;
    int Strength = 0;
    int Dexterity = 0;
    int Intelligence = 0;
    int Luck = 0;
    int CriticalProbability = 0;
    int Gold = 0;
};