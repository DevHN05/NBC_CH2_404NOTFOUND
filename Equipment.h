#pragma once
#include "character.h"
#include "Item.h"

class Equipment : public Item
{
private:
    string equipType;
    int attackBonus;
    int defenseBonus;
    bool equipped;

public:
    Equipment(const string& name, int price, const string& equipType,
        int attackBonus, int defenseBonus)
        : Item(name, price),
        equipType(equipType),
        attackBonus(attackBonus),
        defenseBonus(defenseBonus),
        equipped(false) {
    }

    void Use(Character* character) override 
};

