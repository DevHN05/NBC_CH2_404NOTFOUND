#include "BasePotion.h"
#include <sstream>
#include <iomanip>

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
    if (PotionCounts[GetName()] <= 0)
    {
        cout << "You have no more " << GetName() << " left!" << '\n';
        return;
    }

    switch (PotionType)
    {
    case EPotionType::Health:
        {
            int NewHealth = User.GetHealth() + Recovery;
            User.SetHealth(min(NewHealth, User.GetMaxHealth()));

            cout << "You used " << GetName()
                 << ". Health recovered by " << Recovery
                 << ". Current health: " << User.GetHealth()
                 << "/" << User.GetMaxHealth() << "." << '\n';
            break;
        }

    case EPotionType::Strength:
        {
            int NewStrength = User.GetStrength() + Recovery;
            User.SetStrength(NewStrength);

            cout << "You used " << GetName()
                 << ". strength up " << Recovery
                 << "." << '\n';
            break;
        }
    }

    --PotionCounts[GetName()];
    IsCountRegistered = false;
    cout << "Remaining count of " << GetName() << ": " << PotionCounts[GetName()] << '\n';
}

void BasePotion::ShowInfo() const
{
    cout << "Potion: " << GetName() << '\n';
    cout << "Price: " << GetPrice() << " gold" << '\n';
    cout << "Recovery: " << Recovery << '\n';
    cout << "Count: " << PotionCounts[GetName()] << '\n';
}

unique_ptr<BaseItem> BasePotion::Clone() const
{
    return make_unique<BasePotion>(GetName(), GetPrice(), PotionType, Recovery, true);
}
