#pragma once

#include <memory>
#include <string>
#include <vector>
#include "ItemManager.h"

using namespace std;

class PlayerManager;

class Inventory
{
private:
	vector<unique_ptr<ItemManager>> Items;

public:
    const vector<unique_ptr<ItemManager>>& GetInventoryItems() const;

	void AddItem(unique_ptr<ItemManager> Item);
    ItemManager* FindItem(const string& ItemName) const;
	void UseItem(const string& ItemName, PlayerManager& Character);
	bool RemoveItem(const string& ItemName);
};

