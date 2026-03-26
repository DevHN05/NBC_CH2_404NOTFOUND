#pragma once
#include "character.h"
#include "Item.h"

class Equipment : public Item
{
private:
    string equip_type_;
    int attack_bonus_;
    int defense_bonus_;
    bool is_equipped_;

public:
    Equipment(const string& name, int price, const string& equip_type, int attack_bonus, int defense_bonus)
    : Item(name, price), equip_type_(equip_type), attack_bonus_(attack_bonus), defense_bonus_(defense_bonus), is_equipped_(false) {
    }

    void Use(Character* character) override
};

