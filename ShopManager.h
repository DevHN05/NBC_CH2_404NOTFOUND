//ShopManager.h

#pragma once
#include "ItemManager.h"
#include <vector>
#include <algorithm>
#include <random>

// =====================================================
// 상점은 독립 매니저 클래스
// BaseCharacter& -> 골드/스탯을 직접 수정
//
// 전투 종료 → CombatManager가 EnterShop() 호출
//			→ 입장 여부 확인
//			→ 메뉴 루프 (구매 / 판매 / 나가기)
//			→ ExitShop()
//
// =====================================================

//진희님 요청 내용
//생성할때 아이템 배열에 상점에서 팔거 다 넣기 (완료)
//아이템 배열에서 뽑아 올거라 랜덤 셔플기능

class PlayerManager;

class ShopManager
{
private:
    ShopManager();

    vector<shared_ptr<ItemManager>> ShopItems;
    vector<shared_ptr<ItemManager>> CurrentDisplayItems;

public:
    ShopManager(const ShopManager&) = delete;
    void operator=(const ShopManager&) = delete;

    static ShopManager& GetInstance()
    {
        static ShopManager Instance;
        return Instance;
    }

    void EnterShop(PlayerManager& Player); //입장 여부 확인 → 메뉴 루프
    void RandomShuffleShopItems();

    bool BuyItem(int Index, PlayerManager& Player);
    bool SellItem(const std::string& ItemName, PlayerManager& Player);

};
