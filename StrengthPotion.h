#include "StrengthPotion.h"

void StrengthPotion::Use(BaseCharacter* character)
{
    if (character == nullptr)
    {
        return;
    }

    if (Count <= 0)
    {
        cout << "You have no more " << GetName() << " left!" << '\n';
        return;
    }

    character->SetStrength(character->GetStrength() + Recovery);
    Count--;

    cout << "You used " << GetName()
        << ". Strength increased by " << Recovery
        << ". Current strength: " << character->GetStrength() << "." << '\n';
}

void StrengthPotion::ShowInfo() const
{
    cout << "Potion: " << GetName() << '\n';
    cout << "Price: " << GetPrice() << " gold" << '\n';
    cout << "Strength Bonus: +" << Recovery << '\n';
    cout << "Count: " << Count << '\n';
}
