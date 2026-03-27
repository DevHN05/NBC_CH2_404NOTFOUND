#include "Inventory.h"

using namespace std;

void Inventory::AddItem(shared_ptr<ItemManager> item)
{
    Items.push_back(item);
    cout << item->GetName() << " is add Inventory" << "\n";
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

void Inventory::UseItem(const string& itemName, PlayerManager& character)
{
    auto item = FindItem(itemName);

    if (!item)
    {
        cout << "This item is no inventory" << "\n";
        return;
    }

    item->Use(character);
}


bool Inventory::RemoveItem(const string& itemName)
{
    for (auto it = Items.begin(); it != Items.end(); ++it) {
        if ((*it)->GetName() == itemName) {
            Items.erase(it);
            return true;
        }
    }

    return false;
}
