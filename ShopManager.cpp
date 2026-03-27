//ShopManager.cpp

#include "ShopManager.h"
#include "PlayerManager.h"
#include "Potion.h"
#include "LoggerSystem.h"



ShopManager::ShopManager()
{
	ShopItems.push_back(make_shared<Potion>("Minor Healing Potion", 100, Potion::EPotionType::Health, 30));
    ShopItems.push_back(make_shared<Potion>("Major Healing Potion", 250, Potion::EPotionType::Health, 80));
    ShopItems.push_back(make_shared<Potion>("Minor Strength Potion", 120, Potion::EPotionType::Strength, 5));
    ShopItems.push_back(make_shared<Potion>("Major Strength Potion", 300, Potion::EPotionType::Strength, 15));
}


void ShopManager::EnterShop(PlayerManager& Player) {

    LoggerSystem& Ls = LoggerSystem::GetInstance();
    Ls.LogShopPrompt();

	int EnterChoice;
	cin >> EnterChoice;


	if (EnterChoice != 1) {
	    Ls.LogShopDecline();
		return;
	}

	bool InShop = true;
	int MenuChoice;

	while (InShop) {

	    Ls.LogShopEnter();

		PrintShopMenu(); //-> 이것도 출력필요해요. 밑에는 예시여서

		cin >> MenuChoice;
	    cin.ignore();

		int ItemChoice;
		string ItemToSellName;

		switch (MenuChoice) {
		case 1:
			ShowShopItems(); //-> 이것도 출력필요해요. 밑에는 예시여서
			cin >> ItemChoice;
			BuyItem(ItemChoice, Player);
			break;
		case 2:
			cout << "판매할 아이템 이름 : "; //-> 이것도 출력필요해요. 밑에는 예시여서
			getline(cin, ItemToSellName);
			SellItem(ItemToSellName, Player);
			break;
		case 3:
			//cout << "다음에 또 오시오.\n";
			InShop = false;
			break;
		}

	}

}


void ShopManager::PrintShopMenu() const { //로거에서 구현하면 여기서는 없어질 함수
	cout << "===== 상점 =====\n";
	cout << "1. 아이템 구매\n";
	cout << "2. 아이템 판매\n";
	cout << "3. 상점 나가기\n";
    cout << "선택 : ";
}

void ShopManager::ShowShopItems() const { //로거에서 구현하면 여기서는 없어질 함수

    cout << "===== 아이템  =====\n";
    cout << "1. Minor Healing Potion (100G)\n";
    cout << "2. Major Healing Potion (250G)\n";
    cout << "3. Minor Strength Potion (120G)\n";
    cout << "4. Major Strength Potion (300G)\n";
    cout << "선택 : ";

}



bool ShopManager::BuyItem(int SelectedNumber, PlayerManager& Player) {
    LoggerSystem& Ls = LoggerSystem::GetInstance();
	int ItemIndex = SelectedNumber - 1;
	if (ItemIndex < 0 || ItemIndex >= ShopItems.size()) return false;

	auto Item = ShopItems[ItemIndex]; //상점꺼 객체(shared)

	if (Player.GetGold() < Item->GetPrice()) {
	    Ls.LogInsufficientGold(Player.GetGold(), Item->GetPrice());
		return false;
	}

    Player.CollectItem(ShopItems[ItemIndex]->Clone()); //복제본 만들기

    Player.SetGold(Player.GetGold() - Item->GetPrice());

	Ls.LogBuyItem(Item->GetName(),Item->GetPrice());


	return true;

}

bool ShopManager::SellItem(const std::string& ItemName, PlayerManager& Player) {
    LoggerSystem& Ls = LoggerSystem::GetInstance();
	auto Item = Player.FindItem(ItemName);
	if (Item == nullptr) {
		Ls.LogItemNotFound(ItemName);
		return false;
	}

	int SellPrice = Item->GetPrice() * 6 / 10;
	Player.SetGold(Player.GetGold() + SellPrice);

    Ls.LogSellItem(ItemName, SellPrice);
	Player.RemoveItem(ItemName);

	return true;

}

