// BossMonsterManager.cpp

#include "BossMonsterManager.h"



BossMonsterManager::BossMonsterManager(
            const string&   InName,
            int             InMaxHealth,
            int             InAttack,
            int             InDefense,
            int             InHealthReward,
            int             InGoldReward,
            const string&   InSpecialSkillName,
            int             InSpecialSkillDamage,
            const string&   InDescription) 
    : MonsterManager(InName, InMaxHealth, InAttack, InDefense, InHealthReward, InGoldReward, InDescription)
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

    // 로그 담당자 봐주세요!!!!
    // 전투 화면에 각성 메시지 출력 예시
    //cout << "\n!!! [페이즈 2] " << GetNickname() << " 이(가) 각성했다 !!!\n";
    //cout << "    " << GetSpecialSkillName() << " 사용 가능 / ATK " << GetStrength() << " 으로 증가!\n\n";

}


void BossMonsterManager::PrintCharacterStatus() const {
    cout << "NickName" << GetNickname() << '\n';
    cout << "Health" << GetHealth() << '\n';
    cout << "Strength" << GetStrength() << '\n';
    cout << "Dexterity" << GetDexterity() << '\n';
    cout << "HealthReward" << GetHealthReward() << '\n';
    cout << "GoldReward" << GetGoldReward() << '\n';
    cout << "SpecialSkillName" << GetSpecialSkillName() << '\n';
    cout << "SpecialSkillDamage" << GetSpecialSkillDamage() << '\n';

}