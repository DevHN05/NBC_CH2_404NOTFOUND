#pragma once
#include <map>
#include <vector>
#include <string>
using namespace std;

class Logger
{
public:
    //전투 관련
    void logMonsterAppear(const string& monstername);
    void logAttack(const string& attacker, const string& target, int damage);
    void logMonsterKill(const string& monstername);

    //캐릭터 관련
    void logLevelUp(int newlevel);
    void logPlayerDeath();

    //아이템 관련
    void logItemUse(const string& itemname, const string& effect);

    //보상 관련
    void logExpGain(int amount, int myexp, int maxexp);
    void logGoldGain(int amount);

    //요약
    void printSummary();
    void printEventLog();

private:
	int totalgold_;
	int totalexp_;
	map<string, int> monsterkilllogs_;
	vector<string> eventlogs_; 

};

