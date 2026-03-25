#include "character.h"

using namespace std;

character::character(string nickname)
{
    nickname_ = nickname;
}

string character::get_nickname()
{
    return nickname_;
};

int character::get_level()
{
    return level_;
}

int character::get_experience()
{
    return experience_;
}

int character::get_health()
{
    return health_;
}

int character::get_strength()
{
    return strength_;
}

int character::get_dexterity()
{
    return dexterity_;
}

int character::get_intelligence()
{
    return intelligence_;
}

int character::get_luck()
{
    return luck_;
}

int character::get_critical_probability()
{
    return critical_probability_;
}

int character::get_gold()
{
    return gold_;
}

void character::set_nickname(string nickname)
{
    nickname_ = nickname;
}

void character::set_level(int level)
{
    level_ = level;
}

void character::set_experience(int experience)
{
    experience_ = experience;
}

void character::set_health(int health)
{
    health_ = health;
}

void character::set_strength(int strength)
{
    strength_ = strength;
}

void character::set_dexterity(int dexterity)
{
    dexterity_ = dexterity;
}

void character::set_intelligence(int intelligence)
{
    intelligence_ = intelligence;
}

void character::set_luck(int luck)
{
    luck_ = luck;
}

void character::set_critical_probability(int critical_probability)
{
    critical_probability_ = critical_probability;
}

void character::set_gold(int gold)
{
    gold_ = gold;
}

void character::print_character_status()
{
    cout << nickname_ << '\n';
    cout << level_ << '\n';
    cout << experience_ << '\n';
    cout << health_ << '\n';
    cout << strength_ << '\n';
    cout << dexterity_ << '\n';
    cout << intelligence_ << '\n';
    cout << luck_ << '\n';
    cout << critical_probability_ << '\n';
    cout << gold_ << '\n';
}
