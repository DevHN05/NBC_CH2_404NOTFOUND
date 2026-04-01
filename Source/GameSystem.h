#pragma once
#include <iostream>

using namespace std;

class GameSystem
{
private:
    GameSystem() {};

public:
    GameSystem(const GameSystem&) = delete;
    void operator=(const GameSystem&) = delete;

    static GameSystem& GetInstance()
    {
        static GameSystem Instance;
        return Instance;
    }

    int GetChapter();
    int GetStage();

    void SetChapter(int chapter);
    void SetStage(int stage);

    void StartGame();

private:
    int Chapter = 0;
    int Stage = 0;
};
