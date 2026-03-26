#include "CombatManager.h"
#include "character.h"
#include "GraphicManager.h"
#include <random>

void CombatManager::StartBattle(character& player, character& monster)
{
    GraphicManager& gm = GraphicManager::GetInstance();
    gm.ClearLogs();
    gm.AddLog(monster.get_nickname() + " Detected");

    while (player.get_health() > 0 && monster.get_health() > 0) {
        UpdateBattleUI(player, monster);

        // --- Player Turn ---
        monster.set_health(monster.get_health() - player.get_strength());
        gm.AddLog(player.get_nickname() + " Attack ! -" + to_string(player.get_strength()));

        gm.GoSpace(0, 30); cout << " [ Enter: Next Turn ]                                ";
        cin.ignore(100, '\n');
        cin.get();
        if (monster.get_health() <= 0) break;

        UpdateBattleUI(player, monster);

        // --- Monster Turn ---
        player.set_health(player.get_health() - monster.get_strength());
        gm.AddLog("?? " + monster.get_nickname() + " Attack ! -" + to_string(monster.get_strength()));

        gm.GoSpace(0, 30); cout << " [ Enter: Next Turn ]                                ";
        cin.get();
    }

    UpdateBattleUI(player, monster);
    if (player.get_health() > 0) {
        gm.AddLog("Victory");
        gm.AddLog("Reward");
        //player.set_gold() += 78;
    }
    else {
        gm.AddLog("Fail");
    }
}

void CombatManager::UpdateBattleUI(character& player, character& monster)
{
    GraphicManager& gm = GraphicManager::GetInstance();

    gm.DrawLayout();

    gm.GoSpace(5, 5);  cout << "[ PLAYER STATUS ]";
    gm.GoSpace(5, 7);  cout << "NAME : " << player.get_nickname();
    gm.GoSpace(5, 8);  cout << "HP   : " << player.get_health() << " / 100";
    gm.GoSpace(5, 9);  cout << "LV   : " << player.get_level();

    gm.GoSpace(75, 5);  cout << "[ ENEMY STATUS ]";
    gm.GoSpace(75, 7);  cout << "NAME : " << monster.get_nickname();
    gm.GoSpace(75, 8);  cout << "HP   : " << (monster.get_health() < 0 ? 0 : monster.get_health()) << " / 50"; //Max_Health
    gm.GoSpace(75, 9);  cout << "TYPE : FATAL ERROR BUG";

    gm.GoSpace(72, 21); cout << "- GOLD: " << player.get_gold() << "G";
    gm.GoSpace(72, 22); cout << "- ATK: " << player.get_strength();
    gm.GoSpace(72, 24); cout << "[ Inventory ]";
    gm.GoSpace(72, 25); cout << " 1. Recovery (HP)";
}

void CombatManager::Reward(character& player)
{
    //int expGain = RandomDice(50) + 10;
    //int goldGain = RandomDice(100) + 20;

    //player.set_experience(player.get_experience() + expGain);
    //player.set_gold(player.get_gold() + goldGain);

    //cout << "\n [Reward]\n";
    //cout << " Exp: +" << expGain << "\n";
    //cout << " Gold: +" << goldGain << "\n";

    // 10percentage
    //if (RandomDice(100) <= 10)
    //{
        //cout << "Add Equipment \n";
        //Item Add
    //}

    cout << "--------------------------\n";
}
