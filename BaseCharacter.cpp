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

int BaseCharacter::GetLevel() const
{
    return Level;
}

int BaseCharacter::GetExperience() const
{
    return Experience;
}

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

int BaseCharacter::GetDexterity() const
{
    return Dexterity;
}

int BaseCharacter::GetIntelligence() const
{
    return Intelligence;
}

int BaseCharacter::GetLuck() const
{
    return Luck;
}

int BaseCharacter::GetCriticalProbability() const
{
    return CriticalProbability;
}

int BaseCharacter::GetGold() const
{
    return Gold;
}

void BaseCharacter::SetNickname(string Nickname)
{
    this->Nickname = Nickname;
}

void BaseCharacter::SetLevel(int Level)
{
    this->Level = Level;
}

void BaseCharacter::SetExperience(int Experience)
{
    this->Experience = Experience;
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

void BaseCharacter::SetDexterity(int Dexterity)
{
    this->Dexterity = Dexterity;
}

void BaseCharacter::SetIntelligence(int Intelligence)
{
    this->Intelligence = Intelligence;
}

void BaseCharacter::SetLuck(int Luck)
{
    this->Luck = Luck;
}

void BaseCharacter::SetCriticalProbability(int CriticalProbability)
{
    this->CriticalProbability = CriticalProbability;
}

void BaseCharacter::SetGold(int Gold)
{
    this->Gold = Gold;
}

void BaseCharacter::PrintCharacterStatus()
{
    cout << Nickname << '\n';
    cout << Level << '\n';
    cout << Experience << '\n';
    cout << Health << '\n';
    cout << Strength << '\n';
    cout << Dexterity << '\n';
    cout << Intelligence << '\n';
    cout << Luck << '\n';
    cout << CriticalProbability << '\n';
    cout << Gold << '\n';
}
