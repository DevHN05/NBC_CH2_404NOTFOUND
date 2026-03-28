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
    GraphicManager() { InitializeAssets(); HOut = GetStdHandle(STD_OUTPUT_HANDLE);}

    HANDLE HOut;
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

    void GoSpace(int X, int Y) const;
    void SetConsoleSize(int Width, int Height) const;

    //Draw
    void DrawLayout() const;
    void DrawLobbyStatus(PlayerManager& Player) const;
    void DrawInventoryData(PlayerManager& Player) const;

    string ShowTitle() const;

    void DrawAsciiCombatArt(const string& Player,const string& Monster);
    void DrawAsciiArt(const string& Name,const int& X, const int& Y);

    //System Log
    void AddLog(const string& Log);
    void ClearLogs();

    //Effect
    void HitShake(const string& TargetKey, int StartX, int StartY, int Force);
};
