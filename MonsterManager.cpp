// MonsterManager.cpp

#include "MonsterManager.h"


MonsterManager::MonsterManager(
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

int MonsterManager::GetExperienceReward() const { return ExperienceReward; }

int MonsterManager::GetGoldReward() const  { return GoldReward; }

string MonsterManager::GetDescription() const { return Description; }

bool MonsterManager::IsAlive() const { return GetHealth() > 0; }


// =====================================================
// 전투 메서드
// =====================================================
int MonsterManager::TakeDamage(int InDamage) {     // 방어력 차감 후, 실제로 깎인 HP 반환

    int ActualDamage = max(1, InDamage - GetDexterity()); //최소 1
    int NewHealth = max(0, GetHealth() - ActualDamage);
    SetHealth(NewHealth);
    return ActualDamage;
}

void MonsterManager::ResetHealth() {
    SetHealth(GetMaxHealth());
}



void MonsterManager::PrintCharacterStatus() const {
    cout << "NickName" << GetNickname() << '\n';
    cout << "Health" << GetHealth() << '\n';
    cout << "Strength" << GetStrength() << '\n';
    cout << "ExperienceReward" << GetExperienceReward() << '\n';
    cout << "GoldReward" << GetGoldReward() << '\n';
}
