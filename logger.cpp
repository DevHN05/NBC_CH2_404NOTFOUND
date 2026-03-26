#include "logger.h"
#include <iostream>
 
//전투 관련
void Logger::log_monster_appear(const string& monster_name) //몬스터가 나타났을때 로그 출력하는 함수
{
	string log = "야생의 " + monster_name + "이/가 나타났다!";
	cout << log << "\n";
	event_logs_.push_back(log);
};
void Logger::log_attack(const string & attacker, const string & target, int damage) //공격을 했을 때 로그 출력하는 함수
{
	string log = attacker + "가 " + target + "을 공격합니다! 데미지: " + to_string(damage);
	cout << log << "\n";
	event_logs_.push_back(log);
};
void Logger::log_monster_kill(const string& monster_name) //몬스터를 처치했을때 로그 출력하는 함수(해당 몬스터의 처치수를 ++함)
{
	monster_kill_logs_[monster_name]++;
	string log = monster_name + "을/를 처치했습니다!";
	cout << log << "\n";
	event_logs_.push_back(log);
};

//캐릭터 관련
void Logger::log_levelup(int newlevel) //레벨업 했을때 로그 출력하는 함수 
{
	string msg = "[레벨업!] 레벨이 " + to_string(newlevel) + "로 올랐습니다!";
	cout << msg << "\n";
	event_logs_.push_back(msg);
};
void Logger::log_player_death() //플레이어 사망시 로그 출력하는 함수
{
	string log = " <<플레이어가 사망했습니다. 게임 오버!>>";
	cout << log << "\n";
	event_logs_.push_back(log);
};

//아이템 관련
void Logger::log_item_use(const string& item_name, const string& effect) //아이템 사용시 로그 출력하는 함수(아이템명과 효과)
{
	string log = "[아이템] " + item_name + " 사용! " + effect;
	cout << log << "\n";
	event_logs_.push_back(log);
};
//보상 관련
void Logger::log_exp_gain(int amount, int my_exp, int max_exp) //경험치 획득시 로그 출력하는 함수(얻은량, 현재경험치/레벨업에 필요한 총 경험치)
{
	total_exp_ += amount;
	string log = "경험치를 " + to_string(amount) + "획득! 현재 경험치: " + to_string(my_exp) + " / " + to_string(max_exp);
	event_logs_.push_back(log);
};
void Logger::log_gold_gain(int amount) //골드 획득시 로그 출력하는 함수(얻은량, 현재 골드량)
{
	total_gold_ += amount;
	string log = to_string(amount) + "골드 획득! => 현재 골드: " + to_string(total_gold_);
	event_logs_.push_back(log);
};

//요약
void Logger::print_summary() //처치한 몬스터와 획득한 총 골드와 경험치를 보여주는 함수 
{
	cout << "========== 게임 로그 요약 ==========" << "\n";

	cout << "[처치한 몬스터]" << "\n";
	if (monster_kill_logs_.empty())
	{
		cout << " 처치한 몬스터가 없습니다." << "\n";
	}
	else
	{
		for (auto& entry : monster_kill_logs_)
		{
			cout << "  " << entry.first << " x" << entry.second << "\n";
		}
	}

	cout << "[총 획득 골드]: " << total_gold_ << "골드" << "\n";
	cout << "[총 획득 경험치]: " << total_exp_ << "EXP" << "\n";
	cout << "====================================" << "\n";
};
void Logger::print_event_log() //출력한 로그들을 한번에 보여주는 함수(플레이 이력)
{
	cout << "========== 플레이 이력 ==========" << "\n";
	if (event_logs_.empty())
	{
		cout << "  기록된 이력이 없습니다." << "\n";
	}
	else
	{
		for (const string& log : event_logs_)
		{
			cout << log << "\n";
		}
	}
	cout << "==================================" << "\n";
};