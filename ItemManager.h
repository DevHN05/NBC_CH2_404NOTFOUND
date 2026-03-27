#pragma once
#include <string>
#include "PlayerManager.h"

using namespace std;

class PlayerManager;

class ItemManager
{
protected:
	string Name;
	int Price;

public:
	ItemManager(const string& name, int price) : Name(name), Price(price) {}
	virtual ~ItemManager() = default;

	string GetName() const;

	int GetPrice() const;

	virtual void Use(PlayerManager& character) = 0;
	virtual void ShowInfo() const = 0;
};

