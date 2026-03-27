#include "Potion.h"

void Potion::Use(PlayerManager& User)
{
    /*if (Count <= 0)
    {
        cout << "You have no more " << GetName() << " left!" << '\n';
        return;
    }*/

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

    //Count--;
    //cout << "Remaining count of " << GetName() << ": " << Count << '\n';
}

void Potion::ShowInfo() const
{
    cout << "Potion: " << GetName() << '\n';
    cout << "Price: " << GetPrice() << " gold" << '\n';
    cout << "Recovery: " << Recovery << '\n';
    //cout << "Count: " << Count << '\n';
}

shared_ptr<ItemManager> Potion::Clone() const  {
    return make_shared<Potion>(*this);  // 복사 생성
}
