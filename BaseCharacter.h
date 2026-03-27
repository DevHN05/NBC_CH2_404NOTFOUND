#pragma once
#include <iostream>

using namespace std;

class BaseCharacter
{
public:
    BaseCharacter(string Nickname);

    virtual ~BaseCharacter() = default;

    string GetNickname() const;
    int GetHealth() const;
    int GetMaxHealth() const;
    int GetStrength() const;

    void SetNickname(string Nickname);
    void SetHealth(int Health);
    void SetMaxHealth(int MaxHealth);
    void SetStrength(int Strength);

    virtual void PrintCharacterStatus() const;

private:
    string Nickname = " ";
    int Health = 0;
    int MaxHealth = 0;
    int Strength = 0;
};
