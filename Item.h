#pragma once
#include <string>
#include "character.h"
using namespace std;

class Item
{
protected:
	string name_;
	int price_;

public:
	Item(string& name, int price) : name_(name), price_(price) {}
	virtual ~Item() = default;

	string GetName() const;

	int GetPrice() const;

	virtual void Use(character* character) = 0;
	virtual void ShowInfo() const = 0;
};

