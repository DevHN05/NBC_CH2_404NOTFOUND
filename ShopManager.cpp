//ShopManager.cpp

#include "ShopManager.h"
#include "PlayerManager.h"
#include "Potion.h"
#include "LoggerSystem.h"
#include "GraphicManager.h"
#include <limits>

ShopManager::ShopManager()
{
	ShopItems.push_back(make_shared<Potion>("Minor Healing Potion", 100, Potion::EPotionType::Health, 30));
    ShopItems.push_back(make_shared<Potion>("Major Healing Potion", 250, Potion::EPotionType::Health, 80));
    ShopItems.push_back(make_shared<Potion>("Minor Strength Potion", 120, Potion::EPotionType::Strength, 5));
    ShopItems.push_back(make_shared<Potion>("Major Strength Potion", 300, Potion::EPotionType::Strength, 15));
    ShopItems.push_back(make_shared<Potion>("Major Jin Potion", 250, Potion::EPotionType::Health, 80));
    ShopItems.push_back(make_shared<Potion>("Minor Hui Potion", 120, Potion::EPotionType::Strength, 5));
    ShopItems.push_back(make_shared<Potion>("Major Jang Potion", 300, Potion::EPotionType::Strength, 15));
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
		    Ls.LogPrintShopItems(ShopItems, CurrentDisplayItems);
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
    if (ShopItems.empty())
        return;

    CurrentDisplayItems.clear();

    static random_device rd;
    static mt19937 g(rd());

    auto ShuffledItems = ShopItems;
    shuffle(ShuffledItems.begin(), ShuffledItems.end(), g);

    int DisplayCount = min((int)ShuffledItems.size(), 5);

    for (int i = 0; i < DisplayCount; ++i)
    {
        CurrentDisplayItems.push_back(ShuffledItems[i]);
    }
}

bool ShopManager::BuyItem(int SelectedNumber, PlayerManager& Player)
{
    LoggerSystem& Ls = LoggerSystem::GetInstance();
	int ItemIndex = SelectedNumber - 1;
	if (ItemIndex < 0 || ItemIndex >= CurrentDisplayItems.size()) return false;

	auto Item = CurrentDisplayItems[ItemIndex]; //상점꺼 객체(shared)

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

