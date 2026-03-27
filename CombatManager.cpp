#include "CombatManager.h"
#include "BaseCharacter.h"
#include "PlayerManager.h"
#include "BaseMonster.h"
#include "GraphicManager.h"
#include "LoggerSystem.h"
#include "DiceSystem.h"
#include <random>

void CombatManager::StartBattle(PlayerManager& Player, BaseMonster& Monster)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Ls = LoggerSystem::GetInstance();
    Gm.ClearLogs();
    Ls.LogMonsterAppear(Monster.GetNickname());

    cin.ignore(100, '\n');

    while (Player.GetHealth() > 0 && Monster.GetHealth() > 0)
    {
        UpdateBattleUI(Player, Monster);

        Gm.GoSpace(3, 20);
        cout << "[ Enter: Player Turn ]";
        cin.get();

        // --- Player Turn ---
        Dice.RollDice(24, 10, 2);
        bool IsSuccess = Dice.GetResult();
        int DiceValue = Dice.GetDiceHead();

        int Damage = IsSuccess ? Player.GetStrength() : Player.GetStrength() / 2;

        Ls.LogDiceRoll(DiceValue, IsSuccess);
        Monster.SetHealth(Monster.GetHealth() - Damage);
        Ls.LogAttack(Player.GetNickname(),Monster.GetNickname(),Damage);
        //Gm.AddLog(Player.GetNickname() + " Attack ! -" + to_string(Damage));


        Gm.GoSpace(3, 20);
        cout << "[ Enter: Monster Turn ]";
        //cin.ignore(100, '\n');
        cin.get();

        if (Monster.GetHealth() <= 0) break;

        UpdateBattleUI(Player, Monster);

        // --- Monster Turn ---
        Dice.RollDice(24, 10, 2);
        IsSuccess = Dice.GetResult();
        DiceValue = Dice.GetDiceHead();

        Damage = IsSuccess ? Monster.GetStrength() : Monster.GetStrength() / 2;

        Ls.LogDiceRoll(DiceValue, IsSuccess);
        Player.SetHealth(Player.GetHealth() - Damage);
        Ls.LogAttack(Monster.GetNickname(), Player.GetNickname(), Damage);
    }

    UpdateBattleUI(Player, Monster);

    if (Player.GetHealth() > 0)
    {
        Gm.AddLog("Victory");
        Gm.AddLog("Reward");
        //player.set_gold() += 78;
    }
    else {
        Gm.AddLog("Fail");
    }
}

void CombatManager::UpdateBattleUI(PlayerManager& Player, BaseMonster& Monster)
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    Gm.DrawLayout();

    Gm.GoSpace(5, 2);  cout << "[ PLAYER STATUS ]";
    Gm.GoSpace(5, 3);  cout << "NAME : " << Player.GetNickname();
    Gm.GoSpace(5, 4);  cout << "HP   : " << Player.GetHealth() << " / 100";

    Gm.GoSpace(75, 2);  cout << "[ ENEMY STATUS ]";
    Gm.GoSpace(75, 3);  cout << "NAME : " << Monster.GetNickname();
    Gm.GoSpace(75, 4);  cout << "HP   : " << (Monster.GetHealth() < 0 ? 0 : Monster.GetHealth()) << " / 50"; //Max_Health

    //gm.d("SLIME", 40, 4);

    Gm.DrawInventoryData(Player);
}

void CombatManager::UpdateStoreUI(PlayerManager& Player)
{
    int choice = -1;
    GraphicManager& Gm = GraphicManager::GetInstance();

    Gm.ClearLogs();

    for (int i = 21; i <= 28; i++) {
        Gm.GoSpace(2, i);
        cout << "                                                                            ";
    }

    while (choice != 0)
    {
        Gm.DrawLayout();
        Gm.GoSpace(35, 2); cout << " [ SYSTEM MERCHANT ] ";

        Gm.GoSpace(40, 7);  cout << "1. STANDARD ANTIVIRUS (HP +50) : 100 G";
        Gm.GoSpace(40, 9);  cout << "2. ATK ENHANCEMENT PATCH (ATK+5): 250 G";
        Gm.GoSpace(40, 11); cout << "3. FIREWALL EXPANSION (MAX HP+30): 300 G";
        Gm.GoSpace(40, 13); cout << "0. EXIT TERMINAL";

        Gm.DrawInventoryData(Player);

        Gm.GoSpace(4, 20); cout << "ENTER ITEM NUMBER TO PURCHASE >> ";
        Gm.GoSpace(38, 20);

        if (!(cin >> choice))
        {
            cin.clear(); cin.ignore(100, '\n');
            continue;
        }

        if (choice == 1 && Player.GetGold() >= 100)
        {
            Player.SetGold(Player.GetGold() - 100);
            Player.SetHealth(min(100, Player.GetHealth() + 50));
            Gm.AddLog("[ SUCCESS: ANTIVIRUS DEPLOYED. HP RECOVERED ]");
        }
        else if (choice == 2 && Player.GetGold() >= 250)
        {
            Player.SetGold(Player.GetGold() - 250);
            Player.SetStrength(Player.GetStrength() + 5);
            Gm.AddLog("[ SUCCESS: ATK PATCH APPLIED. POWER UPGRADED ]");
        }
        else if (choice == 0)
        {
            Gm.AddLog("[ SYSTEM: EXITING MERCHANT TERMINAL... ]");
        }
        else
        {
            Gm.AddLog("[ ERROR: INSUFFICIENT CREDITS OR INVALID INPUT ]");
        }
    }
}

void CombatManager::UpdateEventUI(PlayerManager& Player)
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    Gm.ClearLogs();

    for (int i = 21; i <= 28; i++) {
        Gm.GoSpace(2, i);
        cout << "                                                                            ";
    }

    Gm.DrawLayout();
    Gm.DrawInventoryData(Player);

    Gm.GoSpace(10, 8);  cout << ">> DISCOVERED: OBSOLETE HARD DRIVE (MODEL: OLD-GEN)";
    Gm.GoSpace(10, 9);  cout << ">> ATTEMPT DATA RECOVERY? (CAUTION: RISK OF CORRUPTION)";

    Gm.GoSpace(5, 22);  cout << "1. [START RECOVERY] - (PROBABILITY-BASED REWARDS)";
    Gm.GoSpace(5, 23);  cout << "2. [IGNORE DATA]    - (SECURE DISCONNECT)";
    Gm.GoSpace(5, 25);  cout << "COMMAND >> ";

    int choice;
    cin >> choice;

    if (choice == 1)
    {
        if (rand() % 2 == 0)
        {
            int reward = 150;
            Player.SetGold(Player.GetGold() + reward);
            Gm.AddLog("Success! " + to_string(reward) + "G");
        }
        else {
            Player.SetHealth(Player.GetHealth() - 20);
            Gm.AddLog("SYSTEM ERROR: VIRUS DETECTED! HP -20");
        }
    }
    else {
        Gm.AddLog("Run!");
    }

    Gm.GoSpace(5, 27); cout << "[ Press Enter to return ]";
    cin.ignore(100, '\n');
    cin.get();
}

void CombatManager::Reward(PlayerManager& Player)
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

