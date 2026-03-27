//ShopManager.cpp

#include "ShopManager.h"
//#include "HealthPotion.h" //아이템매니저 파생 클래스 필요합니당
//#include "StrengthPotion.h"


//테스트

ShopManager::ShopManager() //포션 4개로 고정이라, 하드 코딩할게요
{
	// 가격에 따라 회복/버프되는 정도 다르게. 생성자 세번째 인자로 회복/버프 수치 넣은 예시
	//ShopItems.push_back(make_shared<HealthPotion>("Minor Healing Potion", 100, 30));
	//ShopItems.push_back(make_shared<HealthPotion>("Major Healing Potion", 250, 80));
	//ShopItems.push_back(make_shared<StrengthPotion>("Minor Strength Potion", 120, 5));
	//ShopItems.push_back(make_shared<StrengthPotion>("Major Strength Potion", 300, 15));
}


void ShopManager::EnterShop(BaseCharacter& Player) { 
	// 상점 입장할건지 물어보는 메시지 출력
	// 예시. 상점에 입장하시겠습니까? (1: 입장 / 0: 거절)

	int EnterChoice;
	cin >> EnterChoice;

	if (EnterChoice != 1) { // 거절
		// 멘트 필요하다고 생각되면 출력
		return;
	}

	bool InShop = true;
	int MenuChoice;

	while (InShop) {
		
		//cout << "\n현재 골드 : " << Player.GetGold() << "G\n";
		PrintShopMenu();

		cout << "선택 : ";
		cin >> MenuChoice;
		
		int ItemChoice;
		string ItemToSellName;

		switch (MenuChoice) {
		case 1: 
			ShowShopItems(); //1~5 중 선택
			cout << "선택 : ";
			cin >> ItemChoice;
			//BuyItem(ItemChoice, Player, Player.MyInventory); //플레이어클래스가 Inventory를 멤버로 가지기
			break;
		case 2: 
			cout << "판매할 아이템 이름 : ";
			getline(cin, ItemToSellName);
			//SellItem(ItemToSellName, Player, Player.MyInventory); 
			break;
		case 3:
			cout << "다음에 또 오시오.\n";
			InShop = false;
			break;
		default:
			cout << "잘못된 입력입니다.\n";
		}
	
	}



}


void ShopManager::PrintShopMenu() const {
	cout << "===== 상점 =====\n";
	cout << "1. 아이템 구매\n";
	cout << "2. 아이템 판매\n";
	cout << "3. 상점 나가기\n";
}

void ShopManager::ShowShopItems() const {
	
	cout << "===== 아이템 =====\n";

	for (size_t i = 0; i < ShopItems.size(); i++)
	{
		cout << i + 1 << ". "
			<< ShopItems[i]->GetName()
			<< " / 가격 : "
			<< ShopItems[i]->GetPrice()
			<< '\n';
	}
	cout << "5. 뒤로가기";
}



bool ShopManager::BuyItem(int SelectedNumber, BaseCharacter* Player, Inventory& PlayerInventory) {
	
	int ItemIndex = SelectedNumber - 1;
	if (ItemIndex < 0 || ItemIndex >= ShopItems.size()) return false;

	auto Item = ShopItems[ItemIndex]; //상점꺼 객체(shared)

	if (Player->GetGold() < Item->GetPrice()) {
		// 골드 부족 메시지 출력
		return false;
	}

	Player->SetGold(Player->GetGold() - Item->GetPrice());
	
	// 구매 완료 메시지 출력

	/*switch (SelectedMenuNumber) {
	case 1:
		PlayerInventory.AddItem(make_shared<HealthPotion>("Minor Healing Potion", 100, 30));
		break;
	case 2:
		PlayerInventory.AddItem(make_shared<HealthPotion>("Major Healing Potion", 250, 80));
		break;
	case 3:
		PlayerInventory.AddItem(make_shared<StrengthPotion>("Minor Strength Potion", 120, 5));
		break;
	case 4:
		PlayerInventory.AddItem(make_shared<StrengthPotion>("Major Strength Potion", 300, 15));
		break;
	}*/

	return true;

}

bool ShopManager::SellItem(const std::string& ItemName, BaseCharacter* Player, Inventory& PlayerInventory) {

	auto Item = PlayerInventory.FindItem(ItemName);
	if (Item == nullptr) {
		//인벤토리에 없는 아이템이라고 메시지
		return false;
	}

	int SellPrice = Item->GetPrice() * 6 / 10;
	Player->SetGold(Player->GetGold() + SellPrice);

	PlayerInventory.RemoveItem(ItemName);
	//판매 완료 메시지 출력

	return true;

}

