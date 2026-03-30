#include "Potion.h"

map<string, int> Potion::PotionCounts;

Potion::Potion(const string& Name, int Price, EPotionType Type, int Recovery, bool IsIncreaseCount)
    : ItemManager(Name, Price), PotionType(Type), Recovery(Recovery), IsCountRegistered(IsIncreaseCount)
{
    if (IsIncreaseCount)
    {
        ++PotionCounts[GetName()];
    }
}

Potion::~Potion()
{
    if (IsCountRegistered && PotionCounts[GetName()] > 0)
    {
        --PotionCounts[GetName()];
    }
}

void Potion::Use(PlayerManager& User)
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

void Potion::ShowInfo() const
{
    cout << "Potion: " << GetName() << '\n';
    cout << "Price: " << GetPrice() << " gold" << '\n';
    cout << "Recovery: " << Recovery << '\n';
    cout << "Count: " << PotionCounts[GetName()] << '\n';
}

shared_ptr<ItemManager> Potion::Clone() const
{
    return make_shared<Potion>(GetName(), GetPrice(), PotionType, Recovery, true);
}
