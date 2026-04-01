#include "Equipment.h"


void Equipment::Use(PlayerManager& character)
{
	if (!isEquipped)
	{
		character.SetStrength(character.GetStrength() + attackBonus);
		/*character->SetDefense(character->GetDefense() + defenseBonus);*/
		isEquipped = true;
		cout << "You equipped " << GetName() << ". Strength increased by " << attackBonus
			 << " and defense increased by " << defenseBonus << ".\n";
	}
    else
    {
		character.SetStrength(character.GetStrength() - attackBonus);
		/*character->SetDefense(character->GetDefense() - defenseBonus);*/
		isEquipped = false;
		cout << "You unequipped " << GetName() << ". Strength decreased by " << attackBonus
			 << " and defense decreased by " << defenseBonus << ".\n";
	}
}

void Equipment::ShowInfo() const
{
	cout << "Equipment: " << BaseItem::GetName() << "\n";
	cout << "Price: " << BaseItem::GetPrice() << " gold" << "\n";
	cout << "Type: " << equipType << "\n";
	cout << "Attack Bonus: " << attackBonus << "\n";
	cout << "Defense Bonus: " << defenseBonus << "\n";
}
