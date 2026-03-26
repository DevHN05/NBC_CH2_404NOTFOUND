#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <deque>

using namespace std;

class GraphicManager 
{
private:
    GraphicManager() {}
    deque<string> GameLogs;

public:
    GraphicManager(const GraphicManager&) = delete;
    void operator=(const GraphicManager&) = delete;

    static GraphicManager& GetInstance() {
        static GraphicManager Instance;
        return Instance;
    }
    void GoSpace(int X, int y);
    void SetConsoleSize(int width, int height);

    void DrawLayout();
    string ShowTitle();

    void AddLog(const string& log);

    void ClearLogs();
};