#include "Equipment.h"
#include "ItemManager.h"

void Equipment::Use(character* character)
{
	if (!isEquipped) {
		character->SetStrength(character->GetStrength() + attackBonus);
		character->SetDefense(character->GetDefense() + defenseBonus);
		isEquipped = true;
		cout << "You equipped " << GetName() << ". Strength increased by " << attackBonus
			 << " and defense increased by " << defenseBonus << "." << endl;
	} else {
		character->SetStrength(character->GetStrength() - attackBonus);
		character->SetDefense(character->GetDefense() - defenseBonus);
		isEquipped = false;
		cout << "You unequipped " << GetName() << ". Strength decreased by " << attackBonus
			 << " and defense decreased by " << defenseBonus << "." << endl;
	}
}

void Equipment::ShowInfo() const
{
	cout << "Equipment: " << ItemManager::GetName() << endl;
	cout << "Price: " << ItemManager::GetPrice() << " gold" << endl;
	cout << "Type: " << equipType << endl;
	cout << "Attack Bonus: " << attackBonus << endl;
	cout << "Defense Bonus: " << defenseBonus << endl;
}