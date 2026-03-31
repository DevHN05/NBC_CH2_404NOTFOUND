//ShopManager.cpp

#include "ShopManager.h"
#include "PlayerManager.h"
#include "LoggerSystem.h"
#include "GraphicManager.h"
#include "BasePotion.h"
#include <algorithm>

ShopManager::ShopManager()
{
	ShopItems.push_back(make_unique<BasePotion>("시리어스 포션", 75, BasePotion::EPotionType::Health, 30));
    ShopItems.push_back(make_unique<BasePotion>("기가진희 포션", 150, BasePotion::EPotionType::Health, 70));
    ShopItems.push_back(make_unique<BasePotion>("민서유기 포션", 300, BasePotion::EPotionType::Health, 150));
    ShopItems.push_back(make_unique<BasePotion>("리더승재 포션", 75, BasePotion::EPotionType::Strength, 5));
    ShopItems.push_back(make_unique<BasePotion>("유민달팽 포션", 120, BasePotion::EPotionType::Strength, 7));
    ShopItems.push_back(make_unique<BasePotion>("별이다섯개오성현 포션", 120, BasePotion::EPotionType::Strength, 10));
    ShopItems.push_back(make_unique<BasePotion>("10월엔 강동욱토버 포션", 300, BasePotion::EPotionType::Strength, 15));
}

void ShopManager::EnterShop(PlayerManager& Player)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Ls = LoggerSystem::GetInstance();

	bool InShop = true;
	int MenuChoice;

    Ls.LogShopEnter();

	while (InShop)
	{
	    Ls.LogPrintShopMenu();

	    Gm.DrawInventoryData(Player);
	    Gm.CommandAddLog("상점 서비스를 선택하세요 >> ");

	    string Input;
	    if (!getline(cin, Input) || Input.empty())
	    {
	        continue; // 빈 입력이면 루프 다시 시작
	    }
	    int MenuChoice = stoi(Input);

		int ItemChoice;
		string ItemToSellName;

	    Gm.DrawInventoryData(Player);

		switch (MenuChoice)
	    {
		case 1:
		    Ls.LogPrintShopItems(CurrentDisplayItems);
		    Gm.DrawInventoryData(Player);
		    Gm.CommandAddLog("구매할 아이템을 선택하세요 >> ");
		    getline(cin, Input);
		    ItemChoice = stoi(Input);
			BuyItem(ItemChoice, Player);
			break;
		case 2:
		    Gm.CommandAddLog("판매할 아이템 이름을 입력하세요 >> ");
		    getline(cin, ItemToSellName);
			SellItem(ItemToSellName, Player);
			break;
		case 3:
			InShop = false;
		    Gm.ClearLogs();
			break;
		}
	}
}


void ShopManager::RandomShuffleShopItems()
{
    /*
     * //상점 prototype
     * vector<unique_ptr<ItemManager>> ShopItems;
     * ShopItems[0] -> Potion A
     * ShopItems[1] -> Potion B
     *
     * vector<ItemManager*> CurrentDisplayItems; //잠깐 참조하기 위해 raw pointer vector
     * CurrentDisplayItems.push_back(item.get());
     * CurrentDisplayItems[0] -> Potion A (같은 객체)
     * CurrentDisplayItems[1] -> Potion B (같은 객체)
     *
     * shuffle(CurrentDisplayItems.begin(), CurrentDisplayItems.end(), g); //raw pointer 순서만 섞기
     * CurrentDisplayItems[0] -> Potion B
     * CurrentDisplayItems[1] -> Potion A
     */

    if (ShopItems.empty())
        return;

    CurrentDisplayItems.clear();

    static random_device rd;
    static mt19937 g(rd());

    for (const auto& item : ShopItems)
    {
        CurrentDisplayItems.push_back(item.get());
    }

    shuffle(CurrentDisplayItems.begin(), CurrentDisplayItems.end(), g);

    int DisplayCount = min((int)CurrentDisplayItems.size(), 5);
    CurrentDisplayItems.resize(DisplayCount);

}

bool ShopManager::BuyItem(int SelectedNumber, PlayerManager& Player)
{
    LoggerSystem& Ls = LoggerSystem::GetInstance();
	int ItemIndex = SelectedNumber - 1;
	if (ItemIndex < 0 || ItemIndex >= CurrentDisplayItems.size()) return false;

	auto& Item = CurrentDisplayItems[ItemIndex]; //상점꺼 객체(shared)

	if (Player.GetGold() < Item->GetPrice())
	{
	    Ls.LogInsufficientGold(Player.GetGold(), Item->GetPrice());
		return false;
	}

    Player.CollectItem(CurrentDisplayItems[ItemIndex]->Clone()); //복제본 만들기

    Player.SetGold(Player.GetGold() - Item->GetPrice());

	Ls.LogBuyItem(Item->GetName(), Item->GetPrice());

	return true;
}

bool ShopManager::SellItem(const std::string& ItemName, PlayerManager& Player)
{
    LoggerSystem& Ls = LoggerSystem::GetInstance();
	auto Item = Player.FindItem(ItemName);

    if (Item == nullptr)
    {
		Ls.LogItemNotFound(ItemName);
		return false;
	}

	int SellPrice = Item->GetPrice() * 6 / 10;
	Player.SetGold(Player.GetGold() + SellPrice);

    Ls.LogSellItem(ItemName, SellPrice);
	Player.RemoveItem(ItemName);

	return true;
}

