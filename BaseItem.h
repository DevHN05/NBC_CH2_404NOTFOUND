#pragma once
#include <string>
#include <iostream>

using namespace std;

class PlayerManager;

class BaseItem
{
protected:
	string Name;
	int Price;

public:
	BaseItem(const string& Name, int Price) : Name(Name), Price(Price) {}
	virtual ~BaseItem() = default;

	string GetName() const;

	int GetPrice() const;

	virtual void Use(PlayerManager& Character) = 0;
	virtual void ShowInfo() const = 0;
    virtual unique_ptr<BaseItem> Clone() const = 0;

    virtual string GetPotionTypeStr() const;
};

