#pragma once
#include <string>
#include <iostream>

using namespace std;

class PlayerManager;

class ItemManager
{
protected:
	string Name;
	int Price;

public:
	ItemManager(const string& Name, int Price) : Name(Name), Price(Price) {}
	virtual ~ItemManager() = default;

	string GetName() const;

	int GetPrice() const;

	virtual void Use(PlayerManager& Character) = 0;
	virtual void ShowInfo() const = 0;
    virtual unique_ptr<ItemManager> Clone() const = 0;
};

