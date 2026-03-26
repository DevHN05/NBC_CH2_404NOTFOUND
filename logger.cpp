#include "logger.h"
#include <iostream>
 
//전투 관련
void Logger::logMonsterAppear(const string& monstername) //몬스터가 나타났을때 로그 출력하는 함수
{
	string log = "야생의 " + monstername + "이/가 나타났다!";
	cout << log << endl;
	eventlogs_.push_back(log);
};
void Logger::logAttack(const string & attacker, const string & target, int damage) //공격을 했을 때 로그 출력하는 함수
{
	string log = attacker + "가 " + target + "을 공격합니다! 데미지: " + to_string(damage);
	cout << log << endl;
	eventlogs_.push_back(log);
};
void Logger::logMonsterKill(const string& monstername) //몬스터를 처치했을때 로그 출력하는 함수(해당 몬스터의 처치수를 ++함)
{
	monsterkilllogs_[monstername]++;
	string log = monstername + "을/를 처치했습니다!";
	cout << log << endl;
	eventlogs_.push_back(log);
};

//캐릭터 관련
void Logger::logLevelUp(int newlevel) //레벨업 했을때 로그 출력하는 함수 
{
	string msg = "[레벨업!] 레벨이 " + to_string(newlevel) + "로 올랐습니다!";
	cout << msg << endl;
	eventlogs_.push_back(msg);
};
void Logger::logPlayerDeath() //플레이어 사망시 로그 출력하는 함수
{
	string log = " <<플레이어가 사망했습니다. 게임 오버!>>";
	cout << log << endl;
	eventlogs_.push_back(log);
};

//아이템 관련
void Logger::logItemUse(const string& itemname, const string& effect) //아이템 사용시 로그 출력하는 함수(아이템명과 효과)
{
	string log = "[아이템] " + itemname + " 사용! " + effect;
	cout << log << endl;
	eventlogs_.push_back(log);
};
//보상 관련
void Logger::logExpGain(int amount, int myexp, int maxexp) //경험치 획득시 로그 출력하는 함수(얻은량, 현재경험치/레벨업에 필요한 총 경험치)
{
	totalexp_ += amount;
	string log = "경험치를 " + to_string(amount) + "획득! 현재 경험치: " + to_string(myexp) + " / " + to_string(maxexp);
	eventlogs_.push_back(log);
};
void Logger::logGoldGain(int amount) //골드 획득시 로그 출력하는 함수(얻은량, 현재 골드량)
{
	totalgold_ += amount;
	string log = to_string(amount) + "골드 획득! => 현재 골드: " + to_string(totalgold_);
	eventlogs_.push_back(log);
};

//요약
void Logger::printSummary() //처치한 몬스터와 획득한 총 골드와 경험치를 보여주는 함수 
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
void Logger::printEventLog() //출력한 로그들을 한번에 보여주는 함수(플레이 이력)
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