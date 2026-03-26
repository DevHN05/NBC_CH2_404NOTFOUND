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
	Item(const string& name, int price);
	virtual ~Item() = default;

	string get_name() const;

	int get_price() const;

	virtual void use(character* character) = 0;
	virtual void show_info() const = 0;
};

