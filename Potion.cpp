#include "Potion.h"
#include <algorithm>

int Potion::GetCount() const
{
	return Count;
}

void Potion::SetCount(int count)
{
	Count = count;
}

void Potion::Use(BaseCharacter& character)
{
	if (Count <= 0)
	{
		cout << "You have no more " << GetName() << " left!" << endl;
		return;
	}

	switch (PotionType)
	{
	case EPotionType::Health:
	{
		int newHealth = character.GetHealth() + Recovery;
		character.SetHealth(min(newHealth, character.GetMaxHealth()));

		cout << "You used " << GetName()
			<< ". Health recovered by " << Recovery
			<< ". Current health: " << character.GetHealth()
			<< "/" << character.GetMaxHealth() << "." << endl;
		break;
	}

	case EPotionType::Strength:
	{
		character.SetStrength(character.GetStrength() + Recovery);
		cout << "You used " << GetName()
			<< ". Strength increased by " << Recovery
			<< ". Current strength: " << character.GetStrength() << "." << endl;
		break;
	}
	

	default:
		cout << "Unknown potion type." << endl;
		return;
	}

	Count--;
	cout << "Remaining count of " << GetName() << ": " << Count << endl;
}