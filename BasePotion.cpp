#include "BasePotion.h"
#include <sstream>
#include <iomanip>
#include "GraphicManager.h"
#include "SoundManager.h"
#include "GameSystem.h"

map<string, int> BasePotion::PotionCounts;

BasePotion::BasePotion(const string& Name, int Price, EPotionType Type, int Recovery, bool IsIncreaseCount)
    : BaseItem(Name, Price), PotionType(Type), Recovery(Recovery), IsCountRegistered(IsIncreaseCount)
{
    if (IsIncreaseCount)
    {
        ++PotionCounts[GetName()];
    }
}

BasePotion::~BasePotion()
{
    if (IsCountRegistered && PotionCounts[GetName()] > 0)
    {
        --PotionCounts[GetName()];
    }
}

const std::map<BasePotion::EPotionType, std::string> BasePotion::PotionTypeNames = {
    {EPotionType::Health, "Health"},
    {EPotionType::Strength, "Strength"}
};

string BasePotion::GetPotionTypeStr() const
{
    auto it = PotionTypeNames.find(PotionType);
    if (it == PotionTypeNames.end()) return "UnKnown";

    string temp = it->second + " +" + to_string(Recovery);
    const int TypeNamesWidth = 8; // 좌정렬: 포션 타입 너비
    const int RecoveryWidth = 5; // 우정렬: (+회복량) 너비

    std::stringstream ss;
    ss << left << setw(TypeNamesWidth) << it->second;
    ss << right << setw(RecoveryWidth) << ("+" + std::to_string(Recovery));

    return ss.str();
}

void BasePotion::Use(PlayerManager& User)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    SoundManager& Sm = SoundManager::GetInstance();
    Sm.RegisterSound(SoundType::PotionSFX, L"BGM/PotionSFX.wav");

    if (PotionCounts[GetName()] <= 0)
    {
        Gm.AddLog("You have no more " + GetName() + " left!");
        return;
    }

    switch (PotionType)
    {
    case EPotionType::Health:
        {
            Sm.PlaySFX(SoundType::PotionSFX);
            int NewHealth = User.GetHealth() + Recovery;
            User.SetHealth(min(NewHealth, User.GetMaxHealth()));

            Gm.AddLog("You used " + GetName()
                 + ". Health recovered by " + to_string(Recovery)
                 + ". Current health: " + to_string(User.GetHealth())
                 + "/" + to_string(User.GetMaxHealth()) + ".");
            break;
        }

    case EPotionType::Strength:
        {
            Sm.PlaySFX(SoundType::PotionSFX);
            int NewStrength = User.GetStrength() + Recovery;
            User.SetStrength(NewStrength);

            Gm.AddLog("You used " + GetName()
                 + ". strength up " + to_string(Recovery)
                 + ".");
            break;
        }
    }

    --PotionCounts[GetName()];
    IsCountRegistered = false;
    Gm.AddLog("Remaining count of " + GetName() + ": " + to_string(PotionCounts[GetName()]));
}

void BasePotion::ShowInfo() const
{
    cout << "Potion: " << GetName() << '\n';
    cout << "Price: " << GetPrice() << " gold" << '\n';
    cout << "Recovery: " << Recovery << '\n';
    cout << "Count: " << PotionCounts[GetName()] << '\n';
}

bool BasePotion::IsUsed() const
{
    if (PotionCounts[GetName()] > 0)
        return true;
    else
        return false;
}

unique_ptr<BaseItem> BasePotion::Clone() const
{
    return make_unique<BasePotion>(GetName(), GetPrice(), PotionType, Recovery, true);
}
