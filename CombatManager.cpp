#include "CombatManager.h"
#include "BaseCharacter.h"
#include "GraphicManager.h"
#include <random>

void CombatManager::StartBattle(BaseCharacter& Player, BaseCharacter& Monster)
{
    GraphicManager& gm = GraphicManager::GetInstance();
    gm.ClearLogs();
    gm.AddLog(Monster.GetNickname() + " Detected");

    while (Player.GetHealth() > 0 && Monster.GetHealth() > 0)
    {
        UpdateBattleUI(Player, Monster);

        // --- Player Turn ---
        Monster.SetHealth(Monster.GetHealth() - Player.GetStrength());
        gm.AddLog(Player.GetNickname() + " Attack ! -" + to_string(Player.GetStrength()));

        gm.GoSpace(0, 30); cout << " [ Enter: Next Turn ]                                ";
        cin.ignore(100, '\n');
        cin.get();
        if (Monster.GetHealth() <= 0) break;

        UpdateBattleUI(Player, Monster);

        // --- Monster Turn ---
        Player.SetHealth(Player.GetHealth() - Monster.GetStrength());
        gm.AddLog("?? " + Monster.GetNickname() + " Attack ! -" + to_string(Monster.GetStrength()));

        //gm.GoSpace(0, 30); cout << " [ Enter: Next Turn ]                                ";
    }

    UpdateBattleUI(Player, Monster);

    if (Player.GetHealth() > 0)
    {
        gm.AddLog("Victory");
        gm.AddLog("Reward");
        //player.set_gold() += 78;
    }
    else {
        gm.AddLog("Fail");
    }
}

void CombatManager::UpdateBattleUI(BaseCharacter& Player, BaseCharacter& Monster)
{
    GraphicManager& gm = GraphicManager::GetInstance();

    gm.DrawLayout();

    gm.GoSpace(5, 2);  cout << "[ PLAYER STATUS ]";
    gm.GoSpace(5, 3);  cout << "NAME : " << Player.GetNickname();
    gm.GoSpace(5, 4);  cout << "HP   : " << Player.GetHealth() << " / 100";

    gm.GoSpace(75, 2);  cout << "[ ENEMY STATUS ]";
    gm.GoSpace(75, 3);  cout << "NAME : " << Monster.GetNickname();
    gm.GoSpace(75, 4);  cout << "HP   : " << (Monster.GetHealth() < 0 ? 0 : Monster.GetHealth()) << " / 50"; //Max_Health

    //gm.d("SLIME", 40, 4);

    gm.GoSpace(72, 21); cout << "- GOLD: " << Player.GetGold() << "G";
    gm.GoSpace(72, 22); cout << "- ATK: " << Player.GetStrength();
    gm.GoSpace(72, 24); cout << "[ Inventory ]";
    gm.GoSpace(72, 25); cout << " 1. Recovery (HP)";
}

void CombatManager::Reward(BaseCharacter& Player)
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
