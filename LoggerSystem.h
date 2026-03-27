#pragma once
#include <map>
#include <vector>
#include <string>
using namespace std;

class LoggerSystem
{
public:
    LoggerSystem(const LoggerSystem&) = delete;
    void operator=(const LoggerSystem&) = delete;

    static LoggerSystem& GetInstance()
    {
        static LoggerSystem Instance;
        return Instance;
    }

    //전투 관련
    void LogMonsterAppear(const string& MonsterName);
    void LogAttack(const string& Attacker, const string& Target, int Damage);
    void LogMonsterKill(const string& MonsterName);
    void LogBossPhaseChange(const string& Nickname, const string& SpecialSkillName, int BoostedStrength);
    void LogDiceRoll(int Head, bool IsSucceeded);

    //캐릭터 관련
    void LogLevelUp(int NewLevel);
    void LogPlayerDeath();

    //아이템 관련
    void LogItemUse(const string& ItemName, const string& Effect);

    //보상 관련
    void LogExpGain(int Amount, int MyExp, int MaxExp);
    void LogGoldGain(int Amount, int MyGold);

    //상점 관련
    void LogShopPrompt();
    void LogShopEnter();
    void LogShopDecline();
    void LogBuyItem(const string& ItemName, int Price);
    void LogInsufficientGold(int MyGold, int RequiredGold);
    void LogSellItem(const string& ItemName, int SellPrice);
    void LogItemNotFound(const string& ItemName);

    //전투 이벤트 내러티브
    void LogEventWanderer(int StrBonus, int DexBonus); //방랑자
    void LogEventGuardian(int DexBonus, int IntBonus); //파수꾼
    void LogEventBreaker(int StrBonus, int IntBonus); //분쇄자
    void LogEventInvader(int DexBonus, int LukBonus); //침략자
    void LogEventAssassin(int StrBonus, int IntBonus); //암살자
    void LogEventBridge(int DexBonus, int LukBonus, int StrBonus); //아래로 쭉 재활용 몬스터
    void LogEventForest(int IntBonus, int LukBonus);
    void LogEventDataNoise(int IntBonus, int LukBonus);
    void LogEventGravity(int LukBonus, int IntBonus);
    void LogEventCliff(int DexBonus, int IntBonus);

    //전투 이벤트 실패 메시지
    void LogEventFailWanderer();
    void LogEventFailGuardian();
    void LogEventFailBreaker();
    void LogEventFailInvader();
    void LogEventFailAssassin();
    void LogEventFailBridge();
    void LogEventFailForest();
    void LogEventFailDataNoise();
    void LogEventFailGravity();
    void LogEventFailCliff();



    //요약
    void PrintSummary();
    void PrintEventLog();

private:
    int TotalGold;
    int TotalExp;
    LoggerSystem() : TotalGold(0), TotalExp(0) {}
    map<string, int> MonsterKillLogs;
    vector<string> EventLogs;
    void PrintMainArea(const vector<string>& Lines);
};

