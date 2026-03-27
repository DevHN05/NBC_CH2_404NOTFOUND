#pragma once
#include "BaseCharacter.h"
#include "ItemManager.h"

class Potion : public ItemManager
{
protected:
    int Recovery;
    int Count;

public:
    Potion(const string& name, int price, int recovery, int count)
        : ItemManager(name, price),
        Recovery(recovery),
        Count(count) {}

    int GetCount() const;
    int GetRecovery() const;
    void SetCount(int count);
    void ShowInfo() const override = 0;
};
