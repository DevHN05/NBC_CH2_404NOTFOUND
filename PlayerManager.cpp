#include "PlayerManager.h"

int PlayerManager::GetLevel()
{
    return Level;
}

int PlayerManager::GetExperience()
{
    return Experience;
}

int PlayerManager::GetDexterity()
{
    return Dexterity;
}

int PlayerManager::GetIntelligence()
{
    return Intelligence;
}

int PlayerManager::GetLuck()
{
    return Luck;
}

int PlayerManager::GetCriticalProbability()
{
    return CriticalProbability;
}

int PlayerManager::GetGold()
{
    return Gold;
}

void PlayerManager::SetLevel(int Level)
{
    this->Level = Level;
}

void PlayerManager::SetExperience(int Experience)
{
    this->Experience = Experience;
}

void PlayerManager::SetDexterity(int Dexterity)
{
    this->Dexterity = Dexterity;
}

void PlayerManager::SetIntelligence(int Intelligence)
{
    this->Intelligence = Intelligence;
}

void PlayerManager::SetLuck(int Luck)
{
    this->Luck = Luck;
}

void PlayerManager::SetCriticalProbability(int CriticalProbability)
{
    this->CriticalProbability = CriticalProbability;
}

void PlayerManager::SetGold(int Gold)
{
    this->Gold = Gold;
}

void PlayerManager::PrintPlayerStatus()
{
    cout << GetNickname() << "\n";
    cout << Level << "\n";
    cout << Experience << "\n";
    cout << GetHealth() << "\n";
    cout << GetStrength() << "\n";
    cout << Dexterity << "\n";
    cout << Intelligence << "\n";
    cout << CriticalProbability << "\n";
    cout << Gold << "\n";
}
