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
void Potion::Use(Character& character)
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
		int newHealth = character.get_health() + Recovery;
		character.set_health(min(newHealth, character.get_maxHealth()));

		cout << "You used " << GetName()
			<< ". Health recovered by " << Recovery
			<< ". Current health: " << character.get_health()
			<< "/" << character.get_maxHealth() << "." << endl;
		break;
	}

	case EPotionType::Strength:
	{
		character.set_strength(character.get_strength() + Recovery);
		cout << "You used " << GetName()
			<< ". Strength increased by " << Recovery
			<< ". Current strength: " << character.get_strength() << "." << endl;
		break;
	}
	

	default:
		cout << "Unknown potion type." << endl;
		return;
	}

	Count--;
	cout << "Remaining count of " << GetName() << ": " << Count << endl;
}