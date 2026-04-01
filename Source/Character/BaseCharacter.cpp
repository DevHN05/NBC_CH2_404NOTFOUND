#include "BaseCharacter.h"

using namespace std;

BaseCharacter::BaseCharacter(string Nickname)
{
    this->Nickname = Nickname;
}

string BaseCharacter::GetNickname() const
{
    return Nickname;
};

int BaseCharacter::GetHealth() const
{
    return Health;
}

int BaseCharacter::GetMaxHealth() const
{
    return MaxHealth;
}

int BaseCharacter::GetStrength() const
{
    return Strength;
}

void BaseCharacter::SetNickname(string Nickname)
{
    this->Nickname = Nickname;
}

void BaseCharacter::SetHealth(int Health)
{
    this->Health = Health;
}

void BaseCharacter::SetMaxHealth(int MaxHealth)
{
    this->MaxHealth = MaxHealth;
}

void BaseCharacter::SetStrength(int Strength)
{
    this->Strength = Strength;
}

void BaseCharacter::PrintCharacterStatus() const
{
    cout << Nickname << '\n';
    cout << Health << '\n';
    cout << Strength << '\n';
}
