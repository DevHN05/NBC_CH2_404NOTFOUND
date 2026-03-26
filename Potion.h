#pragma once
#include "Character.h"
#include "ItemManager.h"


class Potion : public ItemManager
{
private:
    enum class EPotionType
    {
		Health, Strength
	};
    EPotionType PotionType;
    int Recovery;
    int Count;

public:
    Potion(const string& name, int price, EPotionType potionType,
        int recovery, int count)
        : ItemManager(name, price),
        PotionType(potionType),
        Recovery(recovery),
        Count(count) {
    }
    
    void Use(Character& character);

    int GetCount() const
    {
        return Count; 
    }
    void SetCount(int count)
    { 
        Count = count; 
    }
    EPotionType GetPotionType() const { return PotionType; }
    void ShowInfo() const;
};