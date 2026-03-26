#pragma once
#include "BaseCharacter.h"
#include "ItemManager.h"

class Equipment : public ItemManager
{
private:
    string equipType;
    int attackBonus;
    int defenseBonus;
    bool isEquipped;

public:
    Equipment(const string& name, int price, const string& equipType,
        int attackBonus, int defenseBonus)
        : ItemManager(name, price),
        equipType(equipType),
        attackBonus(attackBonus),
        defenseBonus(defenseBonus),
        isEquipped(false) {
    }

    void Use(BaseCharacter* character) override;
	void ShowInfo() const override;
};

