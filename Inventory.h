#pragma once
#include <memory>
#include <string>
#include <vector>
#include "ItemManager.h"
#include "PlayerManager.h"

class Inventory
{
private:
	vector<shared_ptr<ItemManager>> Items;

public:
	void AddItem(shared_ptr<ItemManager> item);
	shared_ptr<ItemManager> FindItem(const string& itemName);
	void UseItem(const string& itemName, PlayerManager& character);
	bool RemoveItem(const string& itemName);
};

