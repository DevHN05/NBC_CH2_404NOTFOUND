#pragma once
#include <map>
#include <vector>
#include <string>
using namespace std;

class LoggerSystem
{
public:
    //전투 관련
    void LogMonsterAppear(const string& MonsterName);
    void LogAttack(const string& Attacker, const string& Target, int Damage);
    void LogMonsterKill(const string& MonsterName);

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
    map<string, int> MonsterKillLogs;
    vector<string> EventLogs;

};

