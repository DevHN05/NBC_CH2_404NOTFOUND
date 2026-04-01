// BaseBossMonster.cpp

#include "BaseBossMonster.h"
#include "../BasicSystem/LoggerSystem.h"

BaseBossMonster::BaseBossMonster(
                const string&   InName,
                int             InMaxHealth,
                int             InAttack,
                int             InExperienceReward,
                int             InGoldReward,
                const string&   InSpecialSkillName,
                int             InSpecialSkillDamage,
                const string&   InDescription):
        BaseMonster(InName, InMaxHealth, InAttack, InExperienceReward, InGoldReward, InDescription),
        SpecialSkillName(InSpecialSkillName),
        SpecialSkillDamage(InSpecialSkillDamage),
        Phase(1),
        PhaseTriggered(false)
{}

// =====================================================
// BossMonsterManager 전용 getter
// =====================================================

int BaseBossMonster::GetPhase() const { return Phase; }

string BaseBossMonster::GetSpecialSkillName() const { return SpecialSkillName; }

int BaseBossMonster::GetSpecialSkillDamage() const { return SpecialSkillDamage; }

// =====================================================
// OnPhaseChange
// =====================================================

void BaseBossMonster::OnPhaseChange()
{
    //조건 미충족 시 아무것도 안 함
    if (PhaseTriggered || GetHealth() > GetMaxHealth() / 2)
        return;

    Phase = 2;
    PhaseTriggered = true;
    int BoostedStrength = static_cast<int>(GetStrength() * 1.5);
    SetStrength(BoostedStrength);

    LoggerSystem::GetInstance().LogBossPhaseChange(GetNickname(), GetSpecialSkillName(), BoostedStrength);
}

void BaseBossMonster::PrintCharacterStatus() const
{
    cout << "NickName" << GetNickname() << '\n';
    cout << "Health" << GetHealth() << '\n';
    cout << "Strength" << GetStrength() << '\n';
    cout << "ExperienceReward" << GetExperienceReward() << '\n';
    cout << "GoldReward" << GetGoldReward() << '\n';
    cout << "SpecialSkillName" << GetSpecialSkillName() << '\n';
    cout << "SpecialSkillDamage" << GetSpecialSkillDamage() << '\n';
}
