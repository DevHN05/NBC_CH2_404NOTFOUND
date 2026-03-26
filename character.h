#pragma once
#include <iostream>

using namespace std;

class character
{
public:
    character(string nickname);

    string get_nickname();
    int get_level();
    int get_experience();
    int get_health();
    int get_strength();
    int get_dexterity();
    int get_intelligence();
    int get_luck();
    int get_critical_probability();
    int get_gold();

    void set_nickname(string nickname);
    void set_level(int level);
    void set_experience(int experience);
    void set_health(int health);
    void set_strength(int strength);
    void set_dexterity(int dexterity);
    void set_intelligence(int intelligence);
    void set_luck(int luck);
    void set_critical_probability(int critical_probability);
    void set_gold(int gold);

    void print_character_status();

private:
    string nickname_ = " ";
    int level_ = 0;
    int experience_ = 0;
    int health_ = 0;
    int strength_ = 0;
    int dexterity_ = 0;
    int intelligence_ = 0;
    int luck_ = 0;
    int critical_probability_ = 0;
    int gold_ = 0;
};