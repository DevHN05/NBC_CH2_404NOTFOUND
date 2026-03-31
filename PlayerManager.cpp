#include "PlayerManager.h"
#include "LoggerSystem.h"
#include "GraphicManager.h"

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

void PlayerManager::LevelUp()
{
    LoggerSystem& Ls = LoggerSystem::GetInstance();
    GraphicManager& Gm = GraphicManager::GetInstance();

    while (GetMaxExperience() <= GetExperience())
    {
        SetExperience(GetExperience() - GetMaxExperience());
        Level++;
        Ls.LogLevelUp(Level);

        Dice.RollDice(24, 10, 2);
        bool IsSuccess = Dice.GetResult();
        int DiceValue = Dice.GetDiceHead();

        int GainStr = 0, GainDex = 0, GainInt = 0, GainLuk = 0;

        if (IsSuccess)
        {
            // 성공했을 때: 3 ~ 6 사이 랜덤 증가
            GainStr = (rand() % 4) + 3;
            GainDex = (rand() % 4) + 3;
            GainInt = (rand() % 4) + 3;
            GainLuk = (rand() % 4) + 3;
            Gm.AddLog("주사위 판정 성공! 스탯이 대폭 상승합니다.");
        }
        else
        {
            // 실패했을 때: 1 ~ 3 사이 랜덤 증가
            GainStr = (rand() % 3) + 1;
            GainDex = (rand() % 3) + 1;
            GainInt = (rand() % 3) + 1;
            GainLuk = (rand() % 3) + 1;
            Gm.AddLog("주사위 판정 실패... 스탯이 소폭 상승합니다.");
        }

        SetStrength(GetStrength() + GainStr);
        SetDexterity(GetDexterity() + GainDex);
        SetIntelligence(GetIntelligence() + GainInt);
        SetLuck(GetLuck() + GainLuk);

        CriticalProbability = Luck / 10;

        MaxExperience = (int)(MaxExperience * 1.2) + (Level * 10);

        string statLog = "ATK+" + to_string(GainStr) + " DEX+" + to_string(GainDex) +
                         " INT+" + to_string(GainInt) + " LUK+" + to_string(GainLuk);
        Gm.AddLog(statLog);

        Sleep(1000);
    }

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
