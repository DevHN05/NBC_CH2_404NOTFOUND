//ShopManager.h


#pragma once
#include "BaseCharacter.h"
#include "ItemManager.h"
#include "Inventory.h"
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



class ShopManager
{
private:

    vector<shared_ptr<ItemManager>> ShopItems;


public:

    ShopManager();

    void EnterShop(BaseCharacter& Player); //입장 여부 확인 → 메뉴 루프
    
    void PrintShopMenu() const;

    void ShowShopItems() const;

    bool BuyItem(int Index, BaseCharacter* Player, Inventory& PlayerInventory);

    bool SellItem(const std::string& ItemName, BaseCharacter* Player, Inventory& PlayerInventory);


};

