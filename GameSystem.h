#pragma once
#include <iostream>

using namespace std;

class GameSystem
{
public:
    int GetChapter();
    int GetStage();
    
    void SetChapter(int chapter);
    void SetStage(int stage);
    
    void StartGame();
private:
    int Chapter = 0;
    int Stage = 0;
};