#pragma once
#include "ItemManager.h"
#include "PlayerManager.h"

class PlayerManager;

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

    void Use(PlayerManager& character) override;
	void ShowInfo() const override;
};

