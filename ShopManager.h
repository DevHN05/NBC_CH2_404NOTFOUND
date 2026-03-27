//ShopManager.h

#pragma once
#include "ItemManager.h"
#include <vector>

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
    vector<shared_ptr<ItemManager>> ShopItems;

public:
    ShopManager();

    void EnterShop(PlayerManager& Player); //입장 여부 확인 → 메뉴 루프
    void PrintShopMenu() const;
    void ShowShopItems() const;

    bool BuyItem(int Index, PlayerManager& Player);
    bool SellItem(const std::string& ItemName, PlayerManager& Player);
};
