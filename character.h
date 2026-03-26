#pragma once
#include <iostream>

using namespace std;

class character
{
public:
    character(string nickname);

    virtual ~character() = default;

    string get_nickname() const;
    int get_level() const;
    int get_experience() const;
    int get_health() const;
    int get_maxHealth() const;
    int get_strength() const;
    int get_dexterity() const;
    int get_intelligence() const;
    int get_luck() const;
    int get_critical_probability() const;
    int get_gold() const;

    void set_nickname(string nickname);
    void set_level(int level);
    void set_experience(int experience);
    void set_health(int health);
    void set_maxHealth(int maxHealth);
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
    int maxHealth_ = 0;
    int strength_ = 0;
    int dexterity_ = 0;
    int intelligence_ = 0;
    int luck_ = 0;
    int critical_probability_ = 0;
    int gold_ = 0;
};