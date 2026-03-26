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

    //캐릭터 관련
    void LogLevelUp(int NewLevel);
    void LogPlayerDeath();

    //아이템 관련
    void LogItemUse(const string& ItemName, const string& Effect);

    //보상 관련
    void LogExpGain(int Amount, int MyExp, int MaxExp);
    void LogGoldGain(int Amount);

    //요약
    void PrintSummary();
    void PrintEventLog();

private:
    int TotalGold;
    int TotalExp;
    LoggerSystem() : TotalGold(0), TotalExp(0) {}
    map<string, int> MonsterKillLogs;
    vector<string> EventLogs;

};

