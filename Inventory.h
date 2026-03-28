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
	vector<shared_ptr<ItemManager>> Items;

public:
    vector<shared_ptr<ItemManager>> GetInventoryItems();

	void AddItem(shared_ptr<ItemManager> Item);
	shared_ptr<ItemManager> FindItem(const string& ItemName);
	void UseItem(const string& ItemName, PlayerManager& Character);
	bool RemoveItem(const string& ItemName);
};

