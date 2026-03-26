// monster.cpp

#include "monster.h"


monster::monster(
            const string& name,
            int           max_health,
            int           attack,
            int           defense,
            int           xp_reward,
            int           gold_reward,
            const string& description)
    : character(name)
    , xp_reward_(xp_reward)
    , description_(description)
{
    set_max_health(max_health);               // HP 상한
    set_health(max_health);                  // 시작 HP = 최대 HP
    set_strength(attack);               // 공격력
    set_dexterity(defense);             // 방어력 (dexterity 재활용)
    set_gold(gold_reward);               // 골드 보상
}

// =====================================================
// monster 전용 getter
// =====================================================

int monster::get_xp_reward() const  { return xp_reward_; }

string monster::get_description() const { return description_; }

bool monster::is_alive() const { return get_health() > 0; }


// =====================================================
// 전투 메서드
// =====================================================
int monster::take_damage(int damage) {     // 방어력(dexterity_) 차감 후, 실제로 깎인 HP 반환
    
    int actual_damage = max(1, damage - get_dexterity()); //최소 1
    int new_health = max(0, get_health() - actual_damage);
    set_health(new_health);
    return actual_damage;
}

void monster::reset_health() {
    set_health(get_max_health());
}