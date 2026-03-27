// MonsterManager.cpp

#include "BaseMonster.h"


BaseMonster::BaseMonster(
            const string& InName,
            int           InMaxHealth,
            int           InAttack,
            int           InExperienceReward,
            int           InGoldReward,
            const string& InDescription)
    : BaseCharacter(InName)
    , ExperienceReward(InExperienceReward)
    , GoldReward(InGoldReward)
    , Description(InDescription)
{
    SetMaxHealth(InMaxHealth);      // HP 상한
    SetHealth(InMaxHealth);         // 시작 HP = 최대 HP
    SetStrength(InAttack);          // 공격력
}

// =====================================================
// MonsterManager 전용 getter
// =====================================================

int BaseMonster::GetExperienceReward() const { return ExperienceReward; }

int BaseMonster::GetGoldReward() const  { return GoldReward; }

string BaseMonster::GetDescription() const { return Description; }

bool BaseMonster::IsAlive() const { return GetHealth() > 0; }


// =====================================================
// 전투 메서드
// =====================================================
void BaseMonster::TakeDamage(int InDamage) {

    int NewHealth = max(0, GetHealth() - InDamage);
    SetHealth(NewHealth);
}

void BaseMonster::ResetHealth() {
    SetHealth(GetMaxHealth());
}



void BaseMonster::PrintCharacterStatus() const {
    cout << "NickName" << GetNickname() << '\n';
    cout << "Health" << GetHealth() << '\n';
    cout << "Strength" << GetStrength() << '\n';
    cout << "ExperienceReward" << GetExperienceReward() << '\n';
    cout << "GoldReward" << GetGoldReward() << '\n';
}
