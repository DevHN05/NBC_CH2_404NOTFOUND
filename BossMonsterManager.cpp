// BossMonsterManager.cpp

#include "BossMonsterManager.h"
#include "LoggerSystem.h"

BossMonsterManager::BossMonsterManager(
            const string&   InName,
            int             InMaxHealth,
            int             InAttack,
            int             InHealthReward,
            int             InGoldReward,
            const string&   InSpecialSkillName,
            int             InSpecialSkillDamage,
            const string&   InDescription) 
    : MonsterManager(InName, InMaxHealth, InAttack, InHealthReward, InGoldReward, InDescription)
    , SpecialSkillName(InSpecialSkillName)
    , SpecialSkillDamage(InSpecialSkillDamage) 
    , Phase(1)
    , PhaseTriggered(false)
{}


// =====================================================
// BossMonsterManager 전용 getter
// =====================================================

int BossMonsterManager::GetPhase() const { return Phase; }

string BossMonsterManager::GetSpecialSkillName() const { return SpecialSkillName; }

int BossMonsterManager::GetSpecialSkillDamage() const { return SpecialSkillDamage; }


// =====================================================
// OnPhaseChange
// =====================================================

void BossMonsterManager::OnPhaseChange() {

    //조건 미충족 시 아무것도 안 함
    if (PhaseTriggered || GetHealth() > GetMaxHealth() / 2)
        return;

    Phase = 2;
    PhaseTriggered = true;
    int BoostedStrength = static_cast<int>(GetStrength() * 1.5);
    SetStrength(BoostedStrength);

    LoggerSystem::GetInstance().LogBossPhaseChange(GetNickname(), GetSpecialSkillName(), BoostedStrength);

}


void BossMonsterManager::PrintCharacterStatus() const {
    cout << "NickName" << GetNickname() << '\n';
    cout << "Health" << GetHealth() << '\n';
    cout << "Strength" << GetStrength() << '\n';
    cout << "HealthReward" << GetHealthReward() << '\n';
    cout << "GoldReward" << GetGoldReward() << '\n';
    cout << "SpecialSkillName" << GetSpecialSkillName() << '\n';
    cout << "SpecialSkillDamage" << GetSpecialSkillDamage() << '\n';

}