#include "GameSystem.h"
#include "BaseCharacter.h"
#include "PlayerManager.h"
#include "BaseMonster.h"
#include "BaseBossMonster.h"
#include "GraphicManager.h"
#include "CombatManager.h"
#include "EventManager.h"
#include <algorithm>
#include <string>

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

    //Gm.SetConsoleSize(160, 90);
    Gm.UpdateWindowSize();

    string Name = Gm.ShowTitle();

    PlayerManager Player(Name);
    Player.SetLevel(1);
    Player.SetHealth(200);
    Player.SetMaxHealth(200);
    Player.SetStrength(20);
    Player.SetDexterity(3);
    Player.SetIntelligence(3);
    Player.SetLuck(2);
    Player.SetCriticalProbability(20);
    Player.SetGold(300);
    Player.SetExperience(20);
    Player.SetMaxExperience(100);

    EventManager Em(Player);

    cout << "Is your nickname " << Player.GetNickname() << "?\n";

    while (true)
    {
        Gm.DrawLayout();

        Gm.DrawLobbyStatus(Player);
        Gm.DrawInventoryData(Player);

        int Choice;
        string Input;

        while (true)
        {
            Gm.GoSpace(3, 20);
            //cout << " Command (1.Search 2.Recovery 3.Quit): ";
            Gm.CommandAddLog(" Command (1.Search 2.Recovery 3.Quit): ");

            getline(cin, Input);

            if (Input.empty())
            {
                continue;
            }

            Choice = stoi(Input);
            break;

        }
        //민서님의 랜덤 이벤트 함수
        Em.TriggerNextEvent();

        //아래 테스트 함수
        continue;
        if (Choice == 1)
        {
            int RandomEvent = 1; //rand() % 3;

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
                BaseMonster Bug("Fatal Error Bug",50,5,5,5);
                Bug.SetHealth(50);
                Bug.SetMaxHealth(50);
                Bug.SetStrength(7);

                Cm.UpdateEventUI(Player,Bug);
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
