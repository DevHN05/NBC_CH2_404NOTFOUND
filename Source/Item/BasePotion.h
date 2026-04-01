#pragma once
#include "../Character/PlayerManager.h"
#include "BaseItem.h"
#include <iostream>
#include <algorithm>
#include <map>

class BasePotion : public BaseItem
{
public:
    enum class EPotionType
    {
        Health,
        Strength
    };

private:
    EPotionType PotionType;
    int Recovery;
    bool IsCountRegistered;
    static map<string, int> PotionCounts; //포션별로 따로 저장되도록 만듦
    static const std::map<EPotionType, std::string> PotionTypeNames;

public:
    BasePotion(const string& Name, int Price, EPotionType Type, int Recovery, bool IsIncreaseCount);

    BasePotion(const string& Name, int Price, EPotionType Type, int Recovery)
        : BasePotion(Name, Price, Type, Recovery, false)
    {}

    ~BasePotion() override;

    string GetPotionTypeStr() const override;
    void Use(PlayerManager& Character) override;
    void ShowInfo() const override;
    bool IsUsed() const override;

    unique_ptr<BaseItem> Clone() const override; //복사 생성
};
