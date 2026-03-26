#include "combatManager.h"
#include "character.h"
#include "graphicManager.h"
#include <random>

void combatManager::start_battle(character& player, character& monster)
{
    graphicManager& gm = graphicManager::get_instance();
    gm.clear_logs();
    gm.add_log(monster.get_nickname() + " Detected");

    while (player.get_health() > 0 && monster.get_health() > 0) {
        update_battle_ui(player, monster);

        // --- Player Turn ---
        monster.set_health(monster.get_health() - player.get_strength());
        gm.add_log(player.get_nickname() + " Attack ! -" + to_string(player.get_strength()));

        gm.go_space(0, 30); cout << " [ Enter: Next Turn ]                                ";
        cin.ignore(100, '\n');
        cin.get();
        if (monster.get_health() <= 0) break;

        update_battle_ui(player, monster);

        // --- Monster Turn ---
        player.set_health(player.get_health() - monster.get_strength());
        gm.add_log("?? " + monster.get_nickname() + " Attack ! -" + to_string(monster.get_strength()));

        gm.go_space(0, 30); cout << " [ Enter: Next Turn ]                                ";
        cin.get();
    }

    update_battle_ui(player, monster);
    if (player.get_health() > 0) {
        gm.add_log("Victory");
        gm.add_log("Reward");
        //player.set_gold() += 78;
    }
    else {
        gm.add_log("Fail");
    }
}

void combatManager::update_battle_ui(character& player, character& monster)
{
    graphicManager& gm = graphicManager::get_instance();

    gm.draw_layout();

    gm.go_space(5, 5);  cout << "[ PLAYER STATUS ]";
    gm.go_space(5, 7);  cout << "NAME : " << player.get_nickname();
    gm.go_space(5, 8);  cout << "HP   : " << player.get_health() << " / 100";
    gm.go_space(5, 9);  cout << "LV   : " << player.get_level();

    gm.go_space(75, 5);  cout << "[ ENEMY STATUS ]";
    gm.go_space(75, 7);  cout << "NAME : " << monster.get_nickname();
    gm.go_space(75, 8);  cout << "HP   : " << (monster.get_health() < 0 ? 0 : monster.get_health()) << " / 50"; //Max_Health
    gm.go_space(75, 9);  cout << "TYPE : FATAL ERROR BUG";

    gm.go_space(72, 21); cout << "- GOLD: " << player.get_gold() << "G";
    gm.go_space(72, 22); cout << "- ATK: " << player.get_strength();
    gm.go_space(72, 24); cout << "[ Inventory ]";
    gm.go_space(72, 25); cout << " 1. Recovery (HP)";
}

int combatManager::random_dice(int dice)
{
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, dice);

    return dis(gen);
}

void combatManager::reward(character& player)
{
    int expGain = random_dice(50) + 10;
    int goldGain = random_dice(100) + 20;

    player.set_experience(player.get_experience() + expGain);
    player.set_gold(player.get_gold() + goldGain);

    cout << "\n [Reward]\n";
    cout << " Exp: +" << expGain << "\n";
    cout << " Gold: +" << goldGain << "\n";

    // 10percentage
    if (random_dice(100) <= 10)
    {
        //cout << "Add Equipment \n";
        //Item Add
    }

    cout << "--------------------------\n";
}
