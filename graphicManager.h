#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <deque>
#include <unordered_map>
#include <vector>

using namespace std;

class GraphicManager 
{
private:
    GraphicManager() { initialize_assets(); }

    deque<string> GameLogs;
    unordered_map<string, vector<string>> AsciiAssets;

private:
    void initialize_assets();

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
    string ShowTitle();
    void DrawAsciiArt(const string& name, int x, int y);

    void AddLog(const string& Log);
    void ClearLogs();
};

// 임시 주석, 삭제 예정