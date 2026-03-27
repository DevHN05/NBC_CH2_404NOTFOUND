#pragma once
#include "PlayerManager.h"
#include "ItemManager.h"
#include <iostream>
#include <algorithm>

class Potion : public ItemManager
{
    enum class EPotionType
    {
        Health,
        Strength
    };
private:
    EPotionType PotionType;
    int Recovery;
    int Count;

public:
    Potion(const string& name, int price, EPotionType type, int recovery, int count)
        : ItemManager(name, price),
        PotionType(type),
        Recovery(recovery),
        Count(count) {}

    void Use(PlayerManager& character) override;
    void ShowInfo() const override;
};
