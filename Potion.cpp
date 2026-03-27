#include "Potion.h"

int Potion::GetCount() const
{
	return Count;
}

int Potion::GetRecovery() const
{
	return Recovery;
}

void Potion::SetCount(int count)
{
	Count = count;
}

