#include "logger.h"
#include <iostream>
 
//전투 관련
void Logger::logMonsterAppear(const string& monstername) 
{
	string log = "야생의 " + monstername + "이/가 나타났다!";
	cout << log << endl;
	eventlogs_.push_back(log);
};
void Logger::logAttack(const string & attacker, const string & target, int damage)
{
	string log = attacker + "가 " + target + "을 공격합니다! 데미지: " + to_string(damage);
	cout << log << endl;
	eventlogs_.push_back(log);
};
void Logger::logMonsterKill(const string& monstername)
{
	monsterkilllogs_[monstername]++;
	string log = monstername + "을/를 처치했습니다!";
	cout << log << endl;
	eventlogs_.push_back(log);
};

//캐릭터 관련
void Logger::logLevelUp(int newlevel)
{
	string msg = "[레벨업!] 레벨이 " + to_string(newlevel) + "로 올랐습니다!";
	cout << msg << endl;
	eventlogs_.push_back(msg);
};
void Logger::logPlayerDeath() 
{
	string log = " <<플레이어가 사망했습니다. 게임 오버!>>";
	cout << log << endl;
	eventlogs_.push_back(log);
};

//아이템 관련
void Logger::logItemUse(const string& itemname, const string& effect)
{
	string log = "[아이템] " + itemname + " 사용! " + effect;
	cout << log << endl;
	eventlogs_.push_back(log);
};
//보상 관련
void Logger::logExpGain(int amount, int myexp, int maxexp)
{
	totalexp_ += amount;
	string log = "경험치를 " + to_string(amount) + "획득! 현재 경험치: " + to_string(myexp) + " / " + to_string(maxexp);
	eventlogs_.push_back(log);
};
void Logger::logGoldGain(int amount)
{
	totalgold_ += amount;
	string log = to_string(amount) + "골드 획득! => 현재 골드: " + to_string(totalgold_);
	eventlogs_.push_back(log);
};

//요약
void Logger::printSummary()
{
	cout << "========== 게임 로그 요약 ==========" << endl;

	cout << "[처치한 몬스터]" << endl;
	if (monsterkilllogs_.empty())
	{
		cout << " 처치한 몬스터가 없습니다." << endl;
	}
	else
	{
		for (auto& entry : monsterkilllogs_)
		{
			cout << "  " << entry.first << " x" << entry.second << endl;
		}
	}

	cout << "[총 획득 골드]: " << totalgold_ << "골드" << endl;
	cout << "[총 획득 경험치]: " << totalexp_ << "EXP" << endl;
	cout << "====================================" << endl;
};
void Logger::printEventLog()
{
	cout << "========== 플레이 이력 ==========" << endl;
	if (eventlogs_.empty())
	{
		cout << "  기록된 이력이 없습니다." << endl;
	}
	else
	{
		for (const string& log : eventlogs_)
		{
			cout << log << endl;
		}
	}
	cout << "==================================" << endl;
};