#pragma once
#include <vector>
#include "ItemManager.h"
#include <Character.h>

class Inventory
{
private:
	vector<shared_ptr<ItemManager>> Items;

public:
	void AddItem(shared_ptr<ItemManager> item);
	shared_ptr<ItemManager> FindItem(const string& itemName);
	void UseItem(const string& itemName, Character* character);
	void ShowItems() const;
};

