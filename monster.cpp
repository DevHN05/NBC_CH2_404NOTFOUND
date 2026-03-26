// monster.cpp

#include "monster.h"


monster::monster(
            const string& name,
            int           maxHp,
            int           attack,
            int           defense,
            int           xpReward,
            int           goldReward,
            const string& description)
    : character(name)
    , maxHp_(maxHp)
    , xpReward_(xpReward)
    , description_(description)
{
    set_health(maxHp);         // 시작 HP = 최대 HP
    set_strength(attack);      // 공격력
    set_dexterity(defense);    // 방어력 (dexterity 재활용)
    set_gold(goldReward);      // 골드 보상
}

// =====================================================
// monster 전용 getter
// =====================================================
int monster::get_maxHp() const { return maxHp_; }

int monster::get_xpReward() const  { return xpReward_; }

string monster::get_description() const { return description_; }

bool monster::isAlive() const { return get_health() > 0; }


// =====================================================
// 전투 메서드
// =====================================================
int monster::takeDamage(int damage) {     // 방어력(dexterity_) 차감 후, 실제로 깎인 HP 반환
    
    int actualDamage = max(1, damage - get_dexterity()); //최소 1
    int newHp = max(0, get_health() - actualDamage);
    set_health(newHp);
    return actualDamage;
}

void monster::resetHp() {
    set_health(maxHp_);
}