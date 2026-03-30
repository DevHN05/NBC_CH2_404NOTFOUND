#pragma once

#include <memory>
#include <string>
#include <vector>
#include "BaseItem.h"

using namespace std;

class PlayerManager;

class Inventory
{
private:
	vector<unique_ptr<BaseItem>> Items;

public:
    const vector<unique_ptr<BaseItem>>& GetInventoryItems() const;

	void AddItem(unique_ptr<BaseItem> Item);
    BaseItem* FindItem(const string& ItemName) const;
	void UseItem(const string& ItemName, PlayerManager& Character);
	bool RemoveItem(const string& ItemName);
};

