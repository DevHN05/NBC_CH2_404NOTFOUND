#include "CombatManager.h"
#include "BaseCharacter.h"
#include "PlayerManager.h"
#include "BaseMonster.h"
#include "BaseBossMonster.h"
#include "GraphicManager.h"
#include "LoggerSystem.h"
#include "DiceSystem.h"
#include "ShopManager.h"
#include "BaseItem.h"
#include "Inventory.h"
#include <random>

void CombatManager::StartBattle(PlayerManager& Player, BaseMonster& Monster)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Ls = LoggerSystem::GetInstance();
    Ls.hideCursor();

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
        int Damage = Player.GetStrength() + Player.GetDexterity() + Player.GetIntelligence();
        Damage = IsSuccess ? Damage : Damage / 2;

        Ls.LogDiceRoll(DiceValue, IsSuccess);

        if (rand() % 100 < Player.GetCriticalProbability() + (Player.GetLuck()/2))
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
        Gm.DrawGameOver(Player);
    }
    Sleep(1000);
    Ls.showCursor();
}

void CombatManager::StartBossBattle(PlayerManager& Player, BaseBossMonster& Boss)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    LoggerSystem& Ls = LoggerSystem::GetInstance();

    Ls.hideCursor();

    Gm.ClearLogs();
    Gm.BossAppearance(Boss.GetNickname());
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
        int Damage = Player.GetStrength() + Player.GetDexterity() + Player.GetIntelligence() + 20;
        Damage = IsSuccess ? Damage : Damage / 2;

        Ls.LogDiceRoll(DiceValue, IsSuccess);

        if (rand() % 100 < Player.GetCriticalProbability() + (Player.GetLuck()/2))
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
            Rage = true;
            Gm.SetRageMode(true);
            Ls.LogBossPhaseChange(Boss.GetNickname(), Boss.GetSpecialSkillName(), Boss.GetStrength());
            //Gm.FlashScreen(0x4F, 100);
        }

        if (Rage)
            Gm.SetRageMode(true);

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
                Gm.GlitchEffect(300);
                Player.SetHealth(Player.GetHealth() - Boss.GetSpecialSkillDamage());
                for(int i = 0; i < 2; i++) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF0);
                    Gm.DrawCombatLayOut();
                    Sleep(50);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
                    Gm.DrawCombatLayOut();
                    Sleep(50);
                }
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

    Gm.SetRageMode(false);

    UpdateBattleUI(Player, Boss);

    if (Player.GetHealth() > 0)
    {
        Ls.LogMonsterKill(Boss.GetNickname());
        Reward(Player, Boss);
    }
    else
    {
        Gm.DrawGameOver(Player);
    }
    Sleep(1000);
    Ls.showCursor();
}

void CombatManager::UpdateBattleUI(PlayerManager& Player, BaseMonster& Monster)
{
    GraphicManager& Gm = GraphicManager::GetInstance();

    Gm.DrawCombatLayOut();
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

void CombatManager::UpdateBagUI(PlayerManager& Player)
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    int LogStartX = 32;
    int LogStartY = 4;

    while (true)
    {
        Gm.ClearLogs();
        Gm.DrawCombatLayOut();
        Gm.GoSpace(LogStartX, LogStartY);
        cout << " [ Inventory ] ";

        const auto& FullInventory = Player.GetPlayerInventory().GetInventoryItems();

        struct ItemGroup { int Count = 0; BaseItem* FirstItem; };
        map<string, ItemGroup> ItemMap;
        vector<string> DisplayOrder;

        for (const auto& Item : FullInventory)
        {
            if (!Item)
                continue;
            string name = Item->GetName();
            if (ItemMap.find(name) == ItemMap.end())
            {
                ItemMap[name] = { 1, Item.get() };
                DisplayOrder.push_back(name);
            }
            else
            {
                ItemMap[name].Count++;
            }
        }

        int InvY = LogStartY + 2;
        if (DisplayOrder.empty())
        {
            Gm.GoSpace(LogStartX, InvY);
            cout << "소유한 아이템이 없습니다.";
            InvY += 2;
        }
        else
        {
            for (int i = 0; i < DisplayOrder.size(); ++i)
            {
                string Name = DisplayOrder[i];
                Gm.GoSpace(LogStartX, InvY);
                string DisplayText = to_string(i + 1) + ". " + Name;
                if (ItemMap[Name].Count > 1) DisplayText += " (x" + to_string(ItemMap[Name].Count) + ")";
                cout << DisplayText;
                InvY += 2;
            }
        }

        Gm.GoSpace(LogStartX, InvY);
        cout << "0. 나가기";
        Gm.DrawAsciiArt("INVENTORY", 93, LogStartY);

        Gm.CommandAddLog("번호를 눌러 아이템을 사용하세요 >> ");
        string Input;
        getline(cin, Input);

        int Select;
        try { if (Input.empty()) continue; Select = stoi(Input); }
        catch (...) { continue; }

        if (Select == 0) break;

        if (Select < 1 || Select > DisplayOrder.size())
        {
            Gm.AddLog("해당 번호에는 아이템이 없습니다.");
            Sleep(500);
        }
        else
        {
            string SelectedName = DisplayOrder[Select - 1];

            BaseItem* TargetItem = ItemMap[SelectedName].FirstItem;

            // 2. 아이템 사용 (스탯 반영 등)
            TargetItem->Use(Player);
            Gm.AddLog(SelectedName + "를 사용하셨습니다.");

            Player.GetPlayerInventory().RemoveItem(SelectedName);

            Gm.DrawInventoryData(Player);
            Sleep(500);
            continue;
        }
    }
}

void CombatManager::Reward(PlayerManager& Player, BaseMonster& Monster)
{
    LoggerSystem& Ls = LoggerSystem::GetInstance();

    int CurrentExp = Player.GetExperience() + Monster.GetExperienceReward();
    int Gold = Monster.GetGoldReward();

    if (Player.GetMaxExperience() <= CurrentExp)
    {
        while (Player.GetMaxExperience() <= CurrentExp)
        {
            CurrentExp -= Player.GetMaxExperience();
            Player.SetExperience(CurrentExp);
            Player.LevelUp();
            Sleep(1000);
        }
    }
    else
    {
        Player.SetExperience(CurrentExp);
    }

    Player.SetGold(Player.GetGold() + Gold);
    Ls.LogExpGain(Monster.GetExperienceReward(),Player.GetExperience(),Player.GetMaxExperience());
    Ls.LogGoldGain(Gold,Player.GetGold());
    cout << "--------------------------\n";
}
