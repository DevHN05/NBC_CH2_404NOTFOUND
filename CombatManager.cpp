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
    cin.ignore(100, '\n');

    while (Player.GetHealth() > 0 && Monster.GetHealth() > 0)
    {
        Gm.GoSpace(3, 20);
        Gm.CommandAddLog("[ Enter: Player Turn ]");
        //cout << "[ Enter: Player Turn ]";
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

        Gm.HitMonsterShake(Monster.GetNickname(),0);
        UpdateBattleUI(Player, Monster);

        if (Monster.GetHealth() <= 0) break;

        Gm.GoSpace(3, 20);
        Gm.CommandAddLog("[ Enter: Monster Turn ]");
        //cout << "[ Enter: Monster Turn ]";
        cin.get();

        // --- Monster Turn ---
        Dice.RollDice(24, 10, 2);
        IsSuccess = Dice.GetResult();
        DiceValue = Dice.GetDiceHead();

        Damage = IsSuccess ? Monster.GetStrength() : Monster.GetStrength() / 2;

        Ls.LogDiceRoll(DiceValue, IsSuccess);
        Player.SetHealth(Player.GetHealth() - Damage);
        Ls.LogAttack(Monster.GetNickname(), Player.GetNickname(), Damage);

        Gm.HitPlayerShake("PLAYER", 0);
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
    Sleep(1000);
}

void CombatManager::StartBossBattle(PlayerManager& Player, BaseBossMonster& Boss)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Ls = LoggerSystem::GetInstance();

    Gm.ClearLogs();
    Ls.LogMonsterAppear(Boss.GetNickname());

    bool Rage = false;

    UpdateBattleUI(Player, Boss);
    cin.ignore(100, '\n');

    while (Player.GetHealth() > 0 && Boss.GetHealth() > 0)
    {
        Gm.GoSpace(3, 20);
        Gm.CommandAddLog("[ Enter: Player Turn ]");
        //cout << "[ Enter: Player Turn ]";
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

        Gm.HitMonsterShake(Boss.GetNickname(),0);
        UpdateBattleUI(Player, Boss);

        if (Boss.GetHealth() <= 0) break;

        Gm.GoSpace(3, 20);
        //cout << "[ Enter: Boss Turn ]";
        Gm.CommandAddLog("[ Enter: Boss Turn ]");
        cin.get();

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
                Gm.HitPlayerShake("PLAYER", 3);
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
    Sleep(1000);
}

void CombatManager::UpdateBattleUI(PlayerManager& Player, BaseMonster& Monster)
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    Gm.DrawLayout();
    Gm.DrawAsciiCombatArt(Player,Monster);
}

void CombatManager::UpdateStoreUI(PlayerManager& Player)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    ShopManager& Sm = ShopManager::GetInstance();

    Gm.ClearLogs();
    Sm.RandomShuffleShopItems();

    Sm.EnterShop(Player);
}

void CombatManager::UpdateEventUI(PlayerManager& Player, BaseMonster& Monster)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Ls = LoggerSystem::GetInstance();

    Gm.ClearLogs();

    Gm.DrawLayout();
    Gm.DrawInventoryData(Player);

    Ls.LogEventAssassin(3,4);

    //Gm.GoSpace(10, 8);  cout << ">> DISCOVERED: OBSOLETE HARD DRIVE (MODEL: OLD-GEN)";
    //Gm.GoSpace(10, 9);  cout << ">> ATTEMPT DATA RECOVERY? (CAUTION: RISK OF CORRUPTION)";

    //Gm.GoSpace(5, 22);  cout << "1. [START RECOVERY] - (PROBABILITY-BASED REWARDS)";
    //Gm.GoSpace(5, 23);  cout << "2. [IGNORE DATA]    - (SECURE DISCONNECT)";
    Gm.GoSpace(3, 20);
    cout << "[ Select ]";

    int choice;
    cin >> choice;

    //Gm.GoSpace(5, 27);  cout << "[ Press Enter to return ]";
    //cin.ignore(100, '\n');
    //cin.get();
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
