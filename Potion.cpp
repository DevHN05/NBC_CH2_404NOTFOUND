#include "Potion.h"

void Potion::Use(PlayerManager& user)
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
            int newHealth = user.GetHealth() + Recovery;
            user.SetHealth(min(newHealth, user.GetMaxHealth()));

            cout << "You used " << GetName()
                 << ". Health recovered by " << Recovery
                 << ". Current health: " << user.GetHealth()
                 << "/" << user.GetMaxHealth() << "." << '\n';
            break;
        }

    case EPotionType::Strength:
        {
            int newStrength = user.GetStrength() + Recovery;
            user.SetStrength(newStrength);

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
