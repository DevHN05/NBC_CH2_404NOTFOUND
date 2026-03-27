#include <iostream>
#include <windows.h>
#include "GameSystem.h"

using namespace std;

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    GameSystem Game;
    Game.StartGame();
    
    return 0;
}