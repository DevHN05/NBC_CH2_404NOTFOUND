#include "CombatManager.h"
#include "character.h"
#include "GraphicManager.h"
#include <random>

void CombatManager::StartBattle(character& Player, character& Monster)
{
    GraphicManager& gm = GraphicManager::GetInstance();
    gm.ClearLogs();
    gm.AddLog(Monster.get_nickname() + " Detected");

    while (Player.get_health() > 0 && Monster.get_health() > 0) 
    {
        UpdateBattleUI(Player, Monster);

        // --- Player Turn ---
        Monster.set_health(Monster.get_health() - Player.get_strength());
        gm.AddLog(Player.get_nickname() + " Attack ! -" + to_string(Player.get_strength()));

        gm.GoSpace(0, 30); cout << " [ Enter: Next Turn ]                                ";
        cin.ignore(100, '\n');
        cin.get();
        if (Monster.get_health() <= 0) break;

        UpdateBattleUI(Player, Monster);

        // --- Monster Turn ---
        Player.set_health(Player.get_health() - Monster.get_strength());
        gm.AddLog("?? " + Monster.get_nickname() + " Attack ! -" + to_string(Monster.get_strength()));

        //gm.GoSpace(0, 30); cout << " [ Enter: Next Turn ]                                ";
    }

    UpdateBattleUI(Player, Monster);
    
    if (Player.get_health() > 0) 
    {
        gm.AddLog("Victory");
        gm.AddLog("Reward");
        //player.set_gold() += 78;
    }
    else {
        gm.AddLog("Fail");
    }
}

void CombatManager::UpdateBattleUI(character& Player, character& Monster)
{
    GraphicManager& gm = GraphicManager::GetInstance();

    gm.DrawLayout();

    gm.GoSpace(5, 2);  cout << "[ PLAYER STATUS ]";
    gm.GoSpace(5, 3);  cout << "NAME : " << Player.get_nickname();
    gm.GoSpace(5, 4);  cout << "HP   : " << Player.get_health() << " / 100";

    gm.GoSpace(75, 2);  cout << "[ ENEMY STATUS ]";
    gm.GoSpace(75, 3);  cout << "NAME : " << Monster.get_nickname();
    gm.GoSpace(75, 4);  cout << "HP   : " << (Monster.get_health() < 0 ? 0 : Monster.get_health()) << " / 50"; //Max_Health

    gm.GoSpace(72, 21); cout << "- GOLD: " << Player.get_gold() << "G";
    gm.GoSpace(72, 22); cout << "- ATK: " << Player.get_strength();
    gm.GoSpace(72, 24); cout << "[ Inventory ]";
    gm.GoSpace(72, 25); cout << " 1. Recovery (HP)";
}

void CombatManager::Reward(character& Player)
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
