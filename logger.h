#pragma once
#include <map>
#include <vector>
#include <string>
using namespace std;

class Logger
{
public:
    //전투 관련
    void log_monster_appear(const string& monster_name);
    void log_attack(const string& attacker, const string& target, int damage);
    void log_monster_kill(const string& monster_name);

    //캐릭터 관련
    void log_levelup(int new_level);
    void log_player_death();

    //아이템 관련
    void log_item_use(const string& item_name, const string& effect);

    //보상 관련
    void log_exp_gain(int amount, int my_exp, int max_exp);
    void log_gold_gain(int amount);

    //요약
    void print_summary();
    void print_event_log();

private:
	int total_gold_;
	int total_exp_;
	map<string, int> monster_kill_logs_;
	vector<string> event_logs_; 

};

