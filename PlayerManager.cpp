#include "PlayerManager.h"

int PlayerManager::GetLevel()
{
    return Level;
}

int PlayerManager::GetExperience()
{
    return Experience;
}

int PlayerManager::GetMaxExperience()
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

void PlayerManager::SetMaxExperience(int MaxExperience)
{
    this->MaxExperience = MaxExperience;
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

void PlayerManager::CollectItem(shared_ptr<ItemManager> Item)
{
    PlayerInventory.AddItem(Item);
}

void PlayerManager::UseItem(const string& ItemName, PlayerManager* Player)
{
    PlayerInventory.UseItem(ItemName, Player);
}

bool PlayerManager::RemoveItem(const string& ItemName)
{
    PlayerInventory.RemoveItem(ItemName);
}

void PlayerManager::ShowItems()
{
    PlayerInventory.ShowItems();
}

shared_ptr<ItemManager> PlayerManager::FindItem(const string& ItemName)
{
    PlayerInventory.FindItem(ItemName);
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
