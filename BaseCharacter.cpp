#include "BaseCharacter.h"

using namespace std;

BaseCharacter::BaseCharacter(string nickname)
{
    nickname_ = nickname;
}

string BaseCharacter::get_nickname() const
{
    return nickname_;
};

int BaseCharacter::get_level() const
{
    return level_;
}

int BaseCharacter::get_experience() const
{
    return experience_;
}

int BaseCharacter::get_health() const
{
    return health_;
}

int BaseCharacter::get_max_health() const
{
    return max_health_;
}

int BaseCharacter::get_strength() const
{
    return strength_;
}

int BaseCharacter::get_dexterity() const
{
    return dexterity_;
}

int BaseCharacter::get_intelligence() const
{
    return intelligence_;
}

int BaseCharacter::get_luck() const
{
    return luck_;
}

int BaseCharacter::get_critical_probability() const
{
    return critical_probability_;
}

int BaseCharacter::get_gold() const
{
    return gold_;
}

void BaseCharacter::set_nickname(string nickname)
{
    nickname_ = nickname;
}

void BaseCharacter::set_level(int level)
{
    level_ = level;
}

void BaseCharacter::set_experience(int experience)
{
    experience_ = experience;
}

void BaseCharacter::set_health(int health)
{
    health_ = health;
}

void BaseCharacter::set_max_health(int maxHealth)
{
    max_health_ = maxHealth;
}

void BaseCharacter::set_strength(int strength)
{
    strength_ = strength;
}

void BaseCharacter::set_dexterity(int dexterity)
{
    dexterity_ = dexterity;
}

void BaseCharacter::set_intelligence(int intelligence)
{
    intelligence_ = intelligence;
}

void BaseCharacter::set_luck(int luck)
{
    luck_ = luck;
}

void BaseCharacter::set_critical_probability(int critical_probability)
{
    critical_probability_ = critical_probability;
}

void BaseCharacter::set_gold(int gold)
{
    gold_ = gold;
}

void BaseCharacter::print_character_status()
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
