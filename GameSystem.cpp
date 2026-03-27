#include "GameSystem.h"
#include "BaseCharacter.h"
#include "PlayerManager.h"
#include "BaseMonster.h"
#include "BaseBossMonster.h"
#include "GraphicManager.h"
#include "CombatManager.h"

using namespace std;

int GameSystem::GetChapter()
{
    return Chapter;
}

int GameSystem::GetStage()
{
    return Stage;
}

void GameSystem::SetChapter(int Chapter)
{
    this->Chapter = Chapter;
}

void GameSystem::SetStage(int Stage)
{
    this->Stage = Stage;
}

void GameSystem::StartGame()
{
    GraphicManager& Gm = GraphicManager::GetInstance();
    CombatManager& Cm = CombatManager::GetInstance();

    Gm.SetConsoleSize(160, 90);

    string Name = Gm.ShowTitle();

    PlayerManager Player(Name);
    Player.SetHealth(100);
    Player.SetStrength(7);
    Player.SetMaxHealth(100);
    Player.SetCriticalProbability(20);

    cout << "Is your nickname " << Player.GetNickname() << "?\n";

    while (true)
    {
        Gm.DrawLayout();

        Gm.GoSpace(5, 2);  cout << ">> FIELD: SYSTEM CORE";
        Gm.GoSpace(40, 8); cout << " [ " << Player.GetNickname() << " ]  Lv." << Player.GetLevel();
        Gm.GoSpace(40, 9); cout << " HP: " << Player.GetHealth() << " / " << Player.GetMaxHealth();

        Gm.GoSpace(40, 10); cout << " STATUS: [";

        for (int i = 0; i < 20; i++)
        {
            if (i < Player.GetHealth() / 5) cout << "■";
            else cout << " ";
        }

        cout << "]";

        Gm.DrawInventoryData(Player);

        //Gm.GoSpace(0, 30);
        Gm.GoSpace(3, 20);
        cout << " Command (1.Search 2.Recovery 3.Quit): ";

        int Choice;

        if (!(cin >> Choice))
        {
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }

        if (Choice == 1)
        {
            int RandomEvent = 0; //rand() % 3;

            switch (RandomEvent)
            {
            case 0:
                Gm.AddLog(" [!] Monster Detected! Battle Progress ...");
                {
                    //BaseMonster Bug("Fatal Error Bug",50,5,5,5);
                    //Bug.SetHealth(50);
                    //Bug.SetMaxHealth(50);
                    //Bug.SetStrength(7);
                    //Cm.StartBattle(Player, Bug);

                    BaseBossMonster BugBoss("Error King", 100, 10, 10, 10, "IndexOut", 17, "Hi");
                    Cm.StartBossBattle(Player, BugBoss);
                }
                break;

            case 1:
                Gm.AddLog(" [@] System Market Accessing...");
                Cm.UpdateStoreUI(Player);
                break;

            case 2:
                Gm.AddLog(" [?] Unknown Signal Detected...");
                //Cm.UpdateEventUI(Player);
                break;
            }

            Gm.GoSpace(0, 31);
            // system("pause");
            Gm.DrawLayout();
        }
        else if (Choice == 2)
        {
            Player.SetHealth(100);
            Gm.AddLog(" >> System Recovery Complete.");
            Sleep(1000);
            Gm.DrawLayout();
        }
        else if (Choice == 3)
        {
            Gm.AddLog("[Game Quit.]");
            Gm.GoSpace(0, 31);
            break;
        }
    }
}
