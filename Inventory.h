#pragma once
#include <memory>
#include <string>
#include <vector>
#include "ItemManager.h"

class PlayerManager;

class Inventory
{
private:
	std::vector<std::shared_ptr<ItemManager>> Items;

public:
	void AddItem(std::shared_ptr<ItemManager> item);
	std::shared_ptr<ItemManager> FindItem(const std::string& itemName);
	void UseItem(const std::string& itemName, PlayerManager& character);
	bool RemoveItem(const std::string& itemName);
};

