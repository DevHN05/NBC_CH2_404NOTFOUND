#include "PlayerManager.h"

PlayerManager::PlayerManager(string Nickname) : BaseCharacter(Nickname)
{
    SetNickname(Nickname);
}

int PlayerManager::GetLevel() const
{
    return Level;
}

int PlayerManager::GetExperience() const
{
    return Experience;
}

int PlayerManager::GetMaxExperience() const
{
    return MaxExperience;
}

int PlayerManager::GetDexterity() const
{
    return Dexterity;
}

int PlayerManager::GetIntelligence() const
{
    return Intelligence;
}

int PlayerManager::GetLuck() const
{
    return Luck;
}

int PlayerManager::GetCriticalProbability() const
{
    return CriticalProbability;
}

int PlayerManager::GetGold() const
{
    return Gold;
}

Inventory& PlayerManager::GetPlayerInventory()
{
    return PlayerInventory;
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

void PlayerManager::CollectItem(std::unique_ptr<BaseItem> Item)
{
    PlayerInventory.AddItem(std::move(Item));
}

void PlayerManager::UseItem(const string& ItemName)
{
    PlayerInventory.UseItem(ItemName, *this);
}

void PlayerManager::RemoveItem(const string& ItemName)
{
    PlayerInventory.RemoveItem(ItemName);
}

BaseItem* PlayerManager::FindItem(const string& ItemName)
{
    return PlayerInventory.FindItem(ItemName);
}

void PlayerManager::PrintPlayerStatus()
{
    cout << GetNickname() << "\n";
    cout << Level << "\n";
    cout << Experience << "\n";
    cout << MaxExperience << "\n";
    cout << GetHealth() << "\n";
    cout << GetStrength() << "\n";
    cout << Dexterity << "\n";
    cout << Intelligence << "\n";
    cout << CriticalProbability << "\n";
    cout << Gold << "\n";
}
