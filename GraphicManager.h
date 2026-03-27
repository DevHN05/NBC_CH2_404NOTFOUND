#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <deque>
#include <unordered_map>
#include <vector>

using namespace std;

class PlayerManager;

class GraphicManager
{
private:
    GraphicManager() { InitializeAssets(); }

    deque<string> GameLogs;
    unordered_map<string, vector<string>> AsciiAssets;

private:
    void InitializeAssets();

public:
    GraphicManager(const GraphicManager&) = delete;
    void operator=(const GraphicManager&) = delete;

    static GraphicManager& GetInstance()
    {
        static GraphicManager Instance;
        return Instance;
    }

    void GoSpace(int X, int Y);
    void SetConsoleSize(int Width, int Height);

    void DrawLayout();
    void DrawInventoryData(PlayerManager& Player);
    string ShowTitle();
    void DrawAsciiArt(const string& Name, int X, int Y);

    void AddLog(const string& Log);
    void ClearLogs();
};
