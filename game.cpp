#include "game.h"
#include "character.h"

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
    string nickname_;
    
    cout << "Type your nickname: ";
    cin >> nickname_;
    
    character character(nickname_);
    
    cout << "Is your nickname " << character.get_nickname() << "?\n";
}