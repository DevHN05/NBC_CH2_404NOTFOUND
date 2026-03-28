#include "CombatManager.h"
#include "BaseCharacter.h"
#include "PlayerManager.h"
#include "BaseMonster.h"
#include "BaseBossMonster.h"
#include "GraphicManager.h"
#include "LoggerSystem.h"
#include "DiceSystem.h"
#include "ShopManager.h"
#include "ItemManager.h"
#include <random>

void CombatManager::StartBattle(PlayerManager& Player, BaseMonster& Monster)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Ls = LoggerSystem::GetInstance();

    Gm.ClearLogs();
    Ls.LogMonsterAppear(Monster.GetNickname());

    UpdateBattleUI(Player, Monster);

    while (Player.GetHealth() > 0 && Monster.GetHealth() > 0)
    {

        Gm.GoSpace(3, 20);
        cout << "[ Enter: Player Turn ]";
        cin.get();

        // --- Player Turn ---
        Dice.RollDice(24, 10, 2);

        bool IsSuccess = Dice.GetResult();
        int DiceValue = Dice.GetDiceHead();
        bool Critical = false;
        int Damage = IsSuccess ? Player.GetStrength() : Player.GetStrength() / 2;

        Ls.LogDiceRoll(DiceValue, IsSuccess);

        if (rand() % 100 < Player.GetCriticalProbability())
        {
            Critical = true;
            Gm.AddLog("Critical!");
        }

        Damage = (Critical? Damage * 2 : Damage);
        Monster.SetHealth(Monster.GetHealth() - Damage);
        Ls.LogAttack(Player.GetNickname(), Monster.GetNickname(), Damage);

        Gm.HitShake("SLIME",74,1,0);
        UpdateBattleUI(Player, Monster);

        Gm.GoSpace(3, 20);
        cout << "[ Enter: Monster Turn ]";
        cin.get();

        if (Monster.GetHealth() <= 0) break;

        // --- Monster Turn ---
        Dice.RollDice(24, 10, 2);
        IsSuccess = Dice.GetResult();
        DiceValue = Dice.GetDiceHead();

        Damage = IsSuccess ? Monster.GetStrength() : Monster.GetStrength() / 2;

        Ls.LogDiceRoll(DiceValue, IsSuccess);
        Player.SetHealth(Player.GetHealth() - Damage);
        Ls.LogAttack(Monster.GetNickname(), Player.GetNickname(), Damage);

        Gm.HitShake("PLAYER",12,5, 0);
        UpdateBattleUI(Player, Monster);
    }

    UpdateBattleUI(Player, Monster);

    if (Player.GetHealth() > 0)
    {
        Ls.LogMonsterKill(Monster.GetNickname());
        Reward(Player, Monster);
    }
    else
    {
        Ls.LogPlayerDeath();
    }
}

void CombatManager::StartBossBattle(PlayerManager& Player, BaseBossMonster& Boss)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Ls = LoggerSystem::GetInstance();

    Gm.ClearLogs();
    Ls.LogMonsterAppear(Boss.GetNickname());

    bool Rage = false;

    UpdateBattleUI(Player, Boss);

    while (Player.GetHealth() > 0 && Boss.GetHealth() > 0)
    {

        Gm.GoSpace(3, 20);
        cout << "[ Enter: Player Turn ]";
        cin.get();



        // --- Player Turn ---
        Dice.RollDice(24, 10, 2);

        bool IsSuccess = Dice.GetResult();
        int DiceValue = Dice.GetDiceHead();
        bool Critical = false;
        int Damage = IsSuccess ? Player.GetStrength() : Player.GetStrength() / 2;

        Ls.LogDiceRoll(DiceValue, IsSuccess);

        if (rand() % 100 < Player.GetCriticalProbability())
        {
            Critical = true;
            Gm.AddLog("Critical!");
        }

        Damage = (Critical? Damage * 2 : Damage);
        Boss.SetHealth(Boss.GetHealth() - Damage);
        Ls.LogAttack(Player.GetNickname(), Boss.GetNickname(), Damage);

        Gm.HitShake("SLIME",74,1,0);
        UpdateBattleUI(Player, Boss);

        Gm.GoSpace(3, 20);
        cout << "[ Enter: Boss Turn ]";
        cin.get();

        if (Boss.GetHealth() <= 0) break;

        // --- Boss Turn ---
        Boss.OnPhaseChange();

        if(Boss.GetPhase() == 2 && !Rage)
        {
            Ls.LogBossPhaseChange(Boss.GetNickname(), Boss.GetSpecialSkillName(), Boss.GetStrength());
            Rage = true;
        }

        Dice.RollDice(24, 10, 2);
        IsSuccess = Dice.GetResult();
        DiceValue = Dice.GetDiceHead();

        Damage = IsSuccess ? Boss.GetStrength() : Boss.GetStrength() / 2;

        Ls.LogDiceRoll(DiceValue, IsSuccess);

        if (Rage)
        {
            Gm.AddLog(Boss.GetNickname() + "가 " + Boss.GetSpecialSkillName() + " 차지중");
            if (IsSuccess)
            {
                Gm.AddLog("[ ATTACK ]" + Boss.GetNickname()+ "의 " + Boss.GetSpecialSkillName() + " 공격");
                Player.SetHealth(Player.GetHealth() - Boss.GetSpecialSkillDamage());
                Gm.HitShake("PLAYER",12,5, 9);
            }
            else
            {
                Player.SetHealth(Player.GetHealth() - Damage);
                Ls.LogAttack(Boss.GetNickname(), Player.GetNickname(), Damage/2);
                Gm.HitShake("PLAYER",12,5, 3);
            }
        }
        else
        {
            Player.SetHealth(Player.GetHealth() - Damage);
            Ls.LogAttack(Boss.GetNickname(), Player.GetNickname(), Damage);
            Gm.HitShake("PLAYER",12,5, 0);
        }

        UpdateBattleUI(Player, Boss);
    }

    UpdateBattleUI(Player, Boss);

    if (Player.GetHealth() > 0)
    {
        Ls.LogMonsterKill(Boss.GetNickname());
        Reward(Player, Boss);
    }
    else
    {
        Ls.LogPlayerDeath();
    }
}

void CombatManager::UpdateBattleUI(PlayerManager& Player, BaseMonster& Monster)
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    Gm.DrawLayout();
    //Monster
    int MonsterStartX = 5;
    Gm.GoSpace(MonsterStartX, 2);  cout << "[ ENEMY STATUS ]";
    Gm.GoSpace(MonsterStartX, 3);  cout << "NAME : " << Monster.GetNickname();
    int MonsterHpBarLen = 20;
    int MonsterHpLen = (Monster.GetMaxHealth() == 0) ? 0 : (Monster.GetHealth() * MonsterHpBarLen / Monster.GetMaxHealth());
    Gm.GoSpace(MonsterStartX, 4);  cout << "HP   : [";
    for(int i=0; i<MonsterHpBarLen; i++)
    {
        if(i < MonsterHpLen) cout << "■";
        else cout << " ";
    }
    cout << "] " << Monster.GetHealth() << " / " << Monster.GetMaxHealth();

    //Player
    int PlayerStartX = 72;
    Gm.GoSpace(PlayerStartX, 13); cout << "[ PLAYER STATUS ]";
    Gm.GoSpace(PlayerStartX, 14); cout << "NAME : " << Player.GetNickname();
    Gm.GoSpace(PlayerStartX, 15); cout << "Lv." << Player.GetLevel() << "   HP: " << Player.GetHealth() << " / " << Player.GetMaxHealth();
    int PlayerHpBarLen = 20;
    int PlayerHpLen = (Monster.GetMaxHealth() == 0) ? 0 : (Player.GetHealth() * PlayerHpBarLen / Player.GetMaxHealth());
    Gm.GoSpace(PlayerStartX, 16);  cout << "HP   : [";
    for(int i=0; i<PlayerHpBarLen; i++)
    {
        if(i < PlayerHpLen) cout << "■";
        else cout << " ";
    }
    cout << "] " << Player.GetHealth() << " / " << Player.GetMaxHealth();

    Gm.DrawAsciiCombatArt("PLAYER", "SLIME"); //전자는 고정 후자는 몬스터 이름 넣어야댐
    Gm.DrawInventoryData(Player);
}

void CombatManager::UpdateStoreUI(PlayerManager& Player)
{
    int choice = -1;
    GraphicManager& Gm = GraphicManager::GetInstance();
    ShopManager& Sm = ShopManager::GetInstance();

    Gm.ClearLogs();
    Sm.RandomShuffleShopItems();

    for (int i = 21; i <= 28; i++) {
        Gm.GoSpace(2, i);
        cout << "                                                                            ";
    }

    while (choice != 0)
    {
        Gm.DrawLayout();
        Gm.GoSpace(30, 3); cout << " [ SYSTEM MERCHANT ] ";

        vector<shared_ptr<ItemManager>> ItemsLog = Sm.GetShopItems();
        int LogStartX = 28;

        for (int i =0; i < ItemsLog.size(); ++i)
        {
            Gm.GoSpace(LogStartX, 6 + 2 * i);
            cout << to_string(i+1) + ". " + ItemsLog[i]->GetName() + " : " + to_string(ItemsLog[i]->GetPrice()) + "G";
        }

        Gm.GoSpace(LogStartX, 16); cout << "0. EXIT TERMINAL";

        Gm.DrawInventoryData(Player);
        Gm.DrawAsciiArt("SHOPKEEPER" , 64, 2);

        string Input;

        while (true)
        {
            Gm.GoSpace(4, 20); cout << "ENTER ITEM NUMBER TO PURCHASE >> ";
            Gm.GoSpace(38, 20);

            getline(cin, Input);

            if (Input.empty())
            {
                continue;
            }

            choice = stoi(Input);
            break;

        }

        //아이템 구매 및 판매 수정예정
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

void CombatManager::UpdateEventUI(PlayerManager& Player, BaseMonster& Monster)
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    Gm.ClearLogs();

    for (int i = 21; i <= 28; i++)
    {
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

    Gm.GoSpace(5, 27);  cout << "[ Press Enter to return ]";
    cin.ignore(100, '\n');
    cin.get();
}

void CombatManager::Reward(PlayerManager& Player, BaseMonster& Monster)
{
    LoggerSystem& Ls = LoggerSystem::GetInstance();

    int CurrentExp = Player.GetExperience() + Monster.GetExperienceReward();
    int Gold = Monster.GetGoldReward();

    Ls.LogExpGain(Monster.GetExperienceReward(),Player.GetExperience(),Player.GetMaxExperience());
    Ls.LogGoldGain(Gold,Player.GetGold());

    if (Player.GetMaxExperience() < CurrentExp)
    {
        //Player.SetMaxExperience(CurrentExp);
        Player.SetExperience(CurrentExp - Player.GetMaxExperience());
        Player.SetLevel(Player.GetLevel() + 1);
        Ls.LogLevelUp(Player.GetLevel());
    }
    else
    {
        Player.SetExperience(CurrentExp);
    }

    Player.SetGold(Player.GetGold() + Gold);

    cout << "--------------------------\n";
}
