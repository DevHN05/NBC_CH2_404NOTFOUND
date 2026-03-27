#pragma once
#include <string>
#include <iostream>
class PlayerManager;

using namespace std;
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

