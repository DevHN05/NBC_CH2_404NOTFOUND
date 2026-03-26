#include "game.h"
#include "character.h"
#include "graphicManager.h"
#include "combatManager.h"

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
    graphicManager& gm = graphicManager::get_instance();
    combatManager& cm = combatManager::get_instance();

    gm.set_console_size(110, 32);

    string name = gm.show_title();
    
    character player(name);
    
    cout << "Is your nickname " << player.get_nickname() << "?\n";

    while (true)
    {
        gm.draw_layout();

        gm.go_space(5, 2);  cout << ">> FIELD: SYSTEM CORE";
        gm.go_space(40, 8); cout << " [ " << player.get_nickname() << " ]  Lv." << player.get_level();
        gm.go_space(40, 9); cout << " HP: " << player.get_health() << " / 100";

        gm.go_space(40, 10); cout << " STATUS: [";
        for (int i = 0; i < 20; i++) {
            if (i < player.get_health() / 5) cout << "■";
            else cout << " ";
        }
        cout << "]";

        gm.go_space(72, 21); cout << "- GOLD: " << player.get_gold() << "G";
        gm.go_space(72, 22); cout << "- ATK: " << player.get_strength();
        gm.go_space(72, 24); cout << "[ Inventory ]";
        gm.go_space(72, 25); cout << " 1. Recovery (HP)";

        gm.go_space(0, 30);
        cout << " Command (1.Search 2.Recovery 3.Quit): ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }

        if (choice == 1) {
            gm.add_log(" Monster Detected! Battle Progress ...");

            character bug("Fatal Error Bug");
            bug.set_health(50);
            bug.set_strength(7);

            cm.start_battle(player, bug);

            gm.go_space(0, 31);
            //system("pause");

            gm.draw_layout();
        }
        else if (choice == 2) 
        {
            player.set_health(100);
            gm.add_log("Recovery");
            Sleep(1000);
        }
        else if (choice == 3) {
            gm.add_log("[Game Quit.]");
            gm.go_space(0, 31);
            break;
        }
    }
}