#include "BaseItem.h"

using namespace std;

string BaseItem::GetName() const
{
	return Name;
}

int BaseItem::GetPrice() const
{
	return Price;
}

string BaseItem::GetPotionTypeStr() const
{
    return "Unknown";
}
