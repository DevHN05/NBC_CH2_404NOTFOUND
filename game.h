#pragma once
#include <iostream>

using namespace std;

class game
{
public:
    int get_chapter();
    int get_stage();
    
    void set_chapter(int chapter);
    void set_stage(int stage);
    
    void start_game();
private:
    int chapter_ = 0;
    int stage_ = 0;
};