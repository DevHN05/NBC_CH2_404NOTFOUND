#include "Inventory.h"

void Inventory::AddItem(shared_ptr<ItemManager> item)
{
    Items.push_back(item);
    cout << item->GetName() << " 이(가) 인벤토리에 추가되었습니다." << endl;
}

void Inventory::AddItem(shared_ptr<ItemManager> item)
{
    Items.push_back(item);
    cout << item->GetName() << " 이(가) 인벤토리에 추가되었습니다." << endl;
}

shared_ptr<ItemManager> Inventory::FindItem(const string& itemName)
{
    for (auto& item : Items)
    {
        if (item->GetName() == itemName)
            return item;
    }
    return nullptr;
}

void Inventory::UseItem(const string& itemName, BaseCharacter* character)
{
    auto item = FindItem(itemName);

    if (!item)
    {
        cout << "해당 아이템이 인벤토리에 없습니다." << endl;
        return;
    }

    item->Use(character);
}
