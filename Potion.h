#pragma once
#include "PlayerManager.h"
#include "ItemManager.h"
#include <iostream>
#include <algorithm>
#include <map>

class Potion : public ItemManager
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

public:
    Potion(const string& Name, int Price, EPotionType Type, int Recovery, bool IsIncreaseCount);

    Potion(const string& Name, int Price, EPotionType Type, int Recovery)
        : Potion(Name, Price, Type, Recovery, false)
    {}

    ~Potion() override;

    void Use(PlayerManager& Character) override;
    void ShowInfo() const override;

    shared_ptr<ItemManager> Clone() const override; //복사 생성
};

//enum class를 public으로 옮김
//타입별로 2종류라 수량 관리는 인벤토리로 빼기
//Count 관련 내용 빼거나 주석처리함
