#include "Inventory.h"

void Inventory::AddItem(std::shared_ptr<ItemManager> item)
{
    Items.push_back(item);
    cout << item->GetName() << " is add Inventory" << endl;
}

std::shared_ptr<ItemManager> Inventory::FindItem(const std::string& itemName)
{
    for (auto& item : Items)
    {
        if (item->GetName() == itemName)
            return item;
    }
    return nullptr;
}

void Inventory::UseItem(const std::string& itemName, PlayerManager& character)
{
    auto item = FindItem(itemName);

    if (!item)
    {
        cout << "This item is no inventory" << endl;
        return;
    }

    item->Use(character);
}


bool Inventory::RemoveItem(const std::string& itemName)
{
    for (auto it = Items.begin(); it != Items.end(); ++it) {
        if ((*it)->GetName() == itemName) {
            Items.erase(it);
            return true;
        }
    }

    return false;
}
