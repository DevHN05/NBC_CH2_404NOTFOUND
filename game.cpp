#include "game.h"
#include "character.h"
#include "GraphicManager.h"
#include "CombatManager.h"

using namespace std;

int game::get_chapter()
{
    return chapter_;
}

int game::get_stage()
{
    return stage_;
}

void game::set_chapter(int chapter)
{
    chapter_ = chapter;
}

void game::set_stage(int stage)
{
    stage_ = stage;
}

void game::start_game()
{
    GraphicManager& gm = GraphicManager::GetInstance();
    CombatManager& cm = CombatManager::GetInstance();

    gm.SetConsoleSize(110, 32);

    string name = gm.ShowTitle();
    
    character player(name);
    
    cout << "Is your nickname " << player.get_nickname() << "?\n";

    while (true)
    {
        gm.DrawLayout();

        gm.GoSpace(5, 2);  cout << ">> FIELD: SYSTEM CORE";
        gm.GoSpace(40, 8); cout << " [ " << player.get_nickname() << " ]  Lv." << player.get_level();
        gm.GoSpace(40, 9); cout << " HP: " << player.get_health() << " / 100";

        gm.GoSpace(40, 10); cout << " STATUS: [";
        for (int i = 0; i < 20; i++) {
            if (i < player.get_health() / 5) cout << "■";
            else cout << " ";
        }
        cout << "]";

        gm.GoSpace(72, 21); cout << "- GOLD: " << player.get_gold() << "G";
        gm.GoSpace(72, 22); cout << "- ATK: " << player.get_strength();
        gm.GoSpace(72, 24); cout << "[ Inventory ]";
        gm.GoSpace(72, 25); cout << " 1. Recovery (HP)";

        gm.GoSpace(0, 30);
        cout << " Command (1.Search 2.Recovery 3.Quit): ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }

        if (choice == 1) {
            gm.AddLog(" Monster Detected! Battle Progress ...");

            character bug("Fatal Error Bug");
            bug.set_health(50);
            bug.set_strength(7);

            cm.StartBattle(player, bug);

            gm.GoSpace(0, 31);
            //system("pause");

            gm.DrawLayout();
        }
        else if (choice == 2) 
        {
            player.set_health(100);
            gm.AddLog("Recovery");
            Sleep(1000);
        }
        else if (choice == 3) {
            gm.AddLog("[Game Quit.]");
            gm.GoSpace(0, 31);
            break;
        }
    }
}