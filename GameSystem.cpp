#include "GameSystem.h"
#include "BaseCharacter.h"
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

    Gm.SetConsoleSize(110, 32);

    string Name = Gm.ShowTitle();
    
    BaseCharacter Player(Name);
    
    cout << "Is your nickname " << Player.GetNickname() << "?\n";

    while (true)
    {
        Gm.DrawLayout();

        Gm.GoSpace(5, 2);  cout << ">> FIELD: SYSTEM CORE";
        Gm.GoSpace(40, 8); cout << " [ " << Player.GetNickname() << " ]  Lv." << Player.GetLevel();
        Gm.GoSpace(40, 9); cout << " HP: " << Player.GetHealth() << " / 100";

        Gm.GoSpace(40, 10); cout << " STATUS: [";
        for (int i = 0; i < 20; i++) {
            if (i < Player.GetHealth() / 5) cout << "■";
            else cout << " ";
        }
        cout << "]";

        Gm.GoSpace(72, 21); cout << "- GOLD: " << Player.GetGold() << "G";
        Gm.GoSpace(72, 22); cout << "- ATK: " << Player.GetStrength();
        Gm.GoSpace(72, 24); cout << "[ Inventory ]";
        Gm.GoSpace(72, 25); cout << " 1. Recovery (HP)";

        Gm.GoSpace(0, 30);
        cout << " Command (1.Search 2.Recovery 3.Store 4. Event 5.Quit): ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }

        if (choice == 1) {
            Gm.AddLog(" Monster Detected! Battle Progress ...");

            BaseCharacter Bug("Fatal Error Bug");
            Bug.SetHealth(50);
            Bug.SetStrength(7);

            Cm.StartBattle(Player, Bug);

            Gm.GoSpace(0, 31);
            //system("pause");

            Gm.DrawLayout();
        }
        else if (choice == 2) 
        {
            Player.SetHealth(100);
            Gm.AddLog("Recovery");
            Sleep(1000);
        }
        else if (choice == 3) 
        {
            Gm.AddLog(" Enter Store ...");

            Cm.UpdateStoreUI(Player);

            Gm.GoSpace(0, 31);
            //system("pause");

            Gm.DrawLayout();
        }
        else if (choice == 4) 
        {
            Gm.AddLog(" Enter Event ...");

            Cm.UpdateEventUI(Player);

            Gm.GoSpace(0, 31);
            //system("pause");

            Gm.DrawLayout();
        }
        else if (choice == 5) 
        {
            Gm.AddLog("[Game Quit.]");
            Gm.GoSpace(0, 31);
            break;
        }
    }
}