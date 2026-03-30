//ShopManager.cpp

#include "ShopManager.h"
#include "PlayerManager.h"
#include "LoggerSystem.h"
#include "GraphicManager.h"
#include "BasePotion.h"
#include <limits>
#include <algorithm>

ShopManager::ShopManager()
{
	ShopItems.push_back(make_unique<BasePotion>("Minor Healing Potion", 100, BasePotion::EPotionType::Health, 30));
    ShopItems.push_back(make_unique<BasePotion>("Major Healing Potion", 250, BasePotion::EPotionType::Health, 80));
    ShopItems.push_back(make_unique<BasePotion>("Minor Strength Potion", 120, BasePotion::EPotionType::Strength, 5));
    ShopItems.push_back(make_unique<BasePotion>("Major Strength Potion", 300, BasePotion::EPotionType::Strength, 15));
    ShopItems.push_back(make_unique<BasePotion>("Major Jin Potion", 250, BasePotion::EPotionType::Health, 80));
    ShopItems.push_back(make_unique<BasePotion>("Minor Hui Potion", 120, BasePotion::EPotionType::Strength, 5));
    ShopItems.push_back(make_unique<BasePotion>("Major Jang Potion", 300, BasePotion::EPotionType::Strength, 15));
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
	    Gm.GoSpace(4, 20); cout << "상점 메뉴 번호를 입력하세요 >> ";

	    string input;
	    getline(cin, input);
	    int MenuChoice = stoi(input);

		int ItemChoice;
		string ItemToSellName;

	    Gm.DrawInventoryData(Player);

		switch (MenuChoice)
	    {
		case 1:
		    Ls.LogPrintShopItems(CurrentDisplayItems);
		    Gm.DrawInventoryData(Player);
		    Gm.GoSpace(4, 20); cout << "구매할 아이템 이름을 입력하세요 >> ";

		    getline(cin, input);
		    ItemChoice = stoi(input);
			BuyItem(ItemChoice, Player);
			break;
		case 2:
		    Gm.GoSpace(4, 20); cout << "판매할 아이템 이름을 입력하세요 >> ";
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
     * vector<ItemManager*> ShuffledItems; //잠깐 참조하기 위해 raw pointer vector
     * ShuffledItems.push_back(item.get());
     * ShuffledItems[0] -> Potion A (같은 객체)
     * ShuffledItems[1] -> Potion B (같은 객체)
     *
     * shuffle(shuffled.begin(), shuffled.end(), g); //raw pointer 순서만 섞기
     * ShuffledItems[0] -> Potion B
     * ShuffledItems[1] -> Potion A
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

