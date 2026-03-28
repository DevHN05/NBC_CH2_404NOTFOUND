#include "Inventory.h"

using namespace std;

vector<shared_ptr<ItemManager>> Inventory::GetInventoryItems()
{
    return Items;
}

void Inventory::AddItem(shared_ptr<ItemManager> Item)
{
    Items.push_back(Item);
    cout << Item->GetName() << " is add Inventory" << "\n";
}

shared_ptr<ItemManager> Inventory::FindItem(const string& ItemName)
{
    for (auto& Item : Items)
    {
        if (Item->GetName() == ItemName)
            return Item;
    }
    return nullptr;
}

void Inventory::UseItem(const string& ItemName, PlayerManager& Character)
{
    auto Item = FindItem(ItemName);

    if (!Item)
    {
        cout << "This item is no inventory" << "\n";
        return;
    }

    Item->Use(Character);
}

bool Inventory::RemoveItem(const string& ItemName)
{
    for (auto It = Items.begin(); It != Items.end(); ++It) {
        if ((*It)->GetName() == ItemName) {
            Items.erase(It);
            return true;
        }
    }

    return false;
}
