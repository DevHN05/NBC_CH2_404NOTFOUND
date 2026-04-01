#pragma once

#include "BaseItem.h"
#include "../Character/PlayerManager.h"

class PlayerManager;

class Equipment : public BaseItem
{
private:
    string equipType;
    int attackBonus;
    int defenseBonus;
    bool isEquipped;

public:
    Equipment(
            const string& name,
            int price,
            const string& equipType,
            int attackBonus,
            int defenseBonus):
        BaseItem(name, price),
        equipType(equipType),
        attackBonus(attackBonus),
        defenseBonus(defenseBonus),
        isEquipped(false)
    {}

    void Use(PlayerManager& character) override;
	void ShowInfo() const override;
};

