#include "Inventory.h"

using namespace std;

const vector<unique_ptr<BaseItem>>& Inventory::GetInventoryItems() const
{
    return Items;
}

void Inventory::AddItem(unique_ptr<BaseItem> Item)
{
    cout << Item->GetName() << " is add Inventory" << "\n";
    Items.push_back(std::move(Item));
}

BaseItem* Inventory::FindItem(const string& ItemName) const
{
    for (auto& Item : Items)
    {
        if (Item->GetName() == ItemName)
            return Item.get();
    }
    return nullptr;
}

void Inventory::UseItem(const string& ItemName, PlayerManager& Character)
{
    const auto Item = FindItem(ItemName);

    if (!Item)
    {
        cout << "This item is no inventory" << "\n";
        return;
    }

    Item->Use(Character);
}

bool Inventory::RemoveItem(const string& ItemName)
{
    auto It = find_if(Items.begin(), Items.end(),
        [&](const unique_ptr<BaseItem>& Item)
        {
            return Item->GetName() == ItemName;
        }
    );

    if (It != Items.end())
    {
        Items.erase(It);
        return true;
    }
    return false;
}
