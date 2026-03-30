#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <deque>
#include <unordered_map>
#include <vector>

using namespace std;

class PlayerManager;
class BaseMonster;

class GraphicManager
{
private:
    GraphicManager() { InitializeAssets(); HOut = GetStdHandle(STD_OUTPUT_HANDLE);}

    HANDLE HOut;
    deque<string> GameLogs;
    unordered_map<string, vector<string>> AsciiAssets;

    //Resolution
    //(0,0) ================================================= (RightEdge, 0)
    //|                                                                    |
    //|                                                                    |
    //|                   [ 메인 화면 (전투/로비 영역) ]                     |
    //|                                                                  |
    //|                                                                 |
    //6//(0, MainBottom) ======================================= (RightEdge, MainBottom)
    //7|    [ 시스템 로그 ]                |                               |
    //8|         [ 커맨드 ]               |     [ 상태창 / 인벤 ]          |
    //9|         (왼쪽 하단)               |      (오른쪽 하단)            |
    //|                                  |                            |
    //11//(0, BottomEdge) ======================================= (RightEdge, BottomEdge)
    //                                   ^
    //                              (SplitColumn)
    int CurrentWidth=120;
    int CurrentHeight=29;
    int MainBottom;
    int SplitColumn;
    int RightEdge;
    int BottomEdge;

    int OffsetX;
    int OffsetY;
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

    //Window
    void GoSpace(int X, int Y) const;
    void SetConsoleSize(int Width, int Height) const;
    void UpdateWindowSize();
    int GetCurrentWidth() const { return CurrentWidth; }
    int GetCurrentHeight() const { return CurrentHeight; }
    int GetMainBottom() const { return MainBottom; }
    int GetSplitColumn() const { return SplitColumn; }

    //Draw
    void DrawLayout() const;
    void DrawCombatLayOut() const;
    void DrawLobbyStatus(PlayerManager& Player) const;
    void DrawInventoryData(PlayerManager& Player) const;
    void DrawGameOver(PlayerManager& Player);
    void DrawDiceRoll(int RollHead, int MaxNumber);
    void DrawCustomDice(int Number, int MaxNumber);

    string ShowTitle() const;

    void DrawAsciiCombatArt(const string& Player,const string& Monster);
    void DrawAsciiCombatArt(PlayerManager& Player, BaseMonster& Monster);
    void DrawAsciiArt(const string& Name,const int& X, const int& Y);
    void DrawAsciiArtCenter(const string& Name);

    //System Log
    void AddLog(const string& Log);
    void CommandAddLog(const string& Log);
    void ClearLogs();

    //Effect
    void HitMonsterShake(const string& TargetKey, int Force);
    void HitPlayerShake(const string& TargetKey, int Force);
    void HitShake(const string& TargetKey, int StartX, int StartY, int Force);

    void BossAppearance(const string& BossKey);
    void GlitchEffect(int DurationMs);
    void InverseFlash(int DurationMs);
    void SetRageMode(bool IsRage);
};
